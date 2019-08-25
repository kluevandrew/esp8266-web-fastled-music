export class Api {
  private socket: WebSocket;
  private counter: number = 0;
  private resolvers: { resolve: (result?: any) => void, reject: (result?: any) => void }[] = [];
  private options: any;
  private currentAnimation: any;
  private callbacks: {[key: string]: ((payload?: any) => void)[]} = {};

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
        this.fireEvent('ws-connect', e);
        resolve(e);
      };
      this.socket.onerror = (e) => {
        this.fireEvent('ws-error', e);
        reject(e);
      };
      this.socket.onclose = (e) => {
        this.fireEvent('ws-close', e);
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
    ++this.counter;
    return new Promise((resolve, reject) => {
      this.resolvers[this.counter] = {resolve, reject};
      this.socket.send(JSON.stringify({id: this.counter, event: event, payload: message}));
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
    this.on('ws-error', callback);
  }

  onReConnect(callback: () => void) {
    this.on('ws-reconnect', callback);
  }

  onConnect(callback: () => void) {
    this.on('ws-connect', callback);
  }

  onClose(callback: () => void) {
    this.on('ws-close', callback);
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

  public connectWifi(ssid: string, password: unknown) {
    return this.send('connectWifi', {ssid, password});
  }
}