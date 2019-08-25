export class Api {
  private socket: WebSocket;
  private counter: number = 0;
  private resolvers: { resolve: (result?: any) => void, reject: (result?: any) => void }[] = [];
  private options: any;
  private currentAnimation: any;
  private callbacks: {[key: string]: ((payload?: any) => void)[]} = {};
  private reconnectTimer = 1000;

  constructor(private host: string) {
  }

  public connect(): Promise<any> {
    return this.connectWs().then(() => {
      return this.loadConfig();
    })
  }

  private connectWs(): Promise<any> {
    return new Promise((resolve, reject) => {
      this.socket = new WebSocket(`ws://${this.host}/ws`, ['arduino']);
      this.socket.binaryType = "arraybuffer";
      this.socket.onopen = (e) => {
        this.fireEvent('ws_connect', e);
        resolve(e);
      };
      this.socket.onerror = (e) => {
        this.fireEvent('ws_error', e);
        this.resolvers = [];
        this.reconnectTimer *= 2;
        setTimeout(() => {
          this.connectWs();
        }, this.reconnectTimer);
        reject(e);
      };
      this.socket.onclose = (e) => {
        this.fireEvent('ws_close', e);
        this.resolvers = [];
        this.reconnectTimer *= 2;
        setTimeout(() => {
          this.connectWs();
        }, this.reconnectTimer);
      };
      this.socket.onmessage = (e) => {
        try {
          let message = JSON.parse(e.data);
          if (!message.id) {
            this.fireEvent(message.event, message);
            return;
          }
          this.resolvers[message.id][message.success ? 'resolve' : 'reject'](message.payload);
        } catch (e) {
        }
      };
    });
  }

  private loadConfig(): Promise<any> {
    return this.send("getOptions", {}).then((response: any) => {
      this.currentAnimation = response.currentAnimation;
      this.options = response.options || {};
    });
  }

  public send(event: any, message: any): Promise<any> {
    const index = ++this.counter;
    return new Promise((resolve, reject) => {
      this.resolvers[index] = {resolve, reject};
      this.socket.send(JSON.stringify({id: this.counter, event: event, payload: message}));
      setTimeout(() => {
        this.resolvers[index] = null;
        reject('timeout');
      }, 5000)
    });
  }

  public setAnimation(name: string): Promise<any> {
    return this.send("setAnimation", { name });
  }

  public setOption(key: string, value: any) {
    return this.send("setOption", { key, value });
  }

  public setColorOption(key: string, hue: number, sat: number, bright: number) {
    return this.send("setColorOption", { key, hue, sat, bright });
  }

  public saveOptions() {
    return this.send("saveOptions", {});
  }

  public resetOptions() {
    return this.send("resetOptions", {});
  }

  public getOption(key: string) {
    return this.options[key];
  }

  public getCurrentAnimation() {
    return this.currentAnimation;
  }

  public getWifiInfo() {
    return this.send("getWifiInfo", {}).then((response) => {
      if (response.networks) {
        response.networks.sort((a, b) => {

          if (a.isHidden && b.isHidden) {
            return a.rssi > b.rssi ? -1 : 1;
          }

          if (a.isHidden) {
            return 1;
          }

          if (b.isHidden) {
            return -1;
          }

          if (a.rssi === b.rssi) {
            return a.ssid.localeCompare(b.ssid);
          }

          return a.rssi > b.rssi ? -1 : 1;
        })
      }
      return response;
    });
  }

  onError(callback: () => void) {
    this.on('ws_error', callback);
  }

  onConnect(callback: () => void) {
    this.on('ws_connect', callback);
  }

  onClose(callback: () => void) {
    this.on('ws_close', callback);
  }

  private fireEvent(event: string | any | Event, payload: any = {}) {
    const callbacks = this.callbacks[event] || [];
    callbacks.forEach((callback: (payload?: any) => void) => {
      callback(payload);
    });
  }

  public on(event: string, callback: (payload?: any) => void) {
    this.callbacks[event] = this.callbacks[event] || [];
    this.callbacks[event].push(callback);
  }

  public off(event: string, callback: (payload?: any) => void) {
    this.callbacks[event] = this.callbacks[event] || [];
    const index = this.callbacks[event].indexOf(callback);
    if (index > -1) {
      this.callbacks[event].splice(index, 1);
    }
  }

  public connectWifi(ssid: string, pass: unknown) {
    return this.send('connectWifi', {ssid, pass});
  }

  public resetWifi() {
    return this.send('resetWifi', {});
  }
}