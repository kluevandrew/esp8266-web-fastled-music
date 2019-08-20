export class Api {
  private socket: WebSocket;
  private counter: number = 0;
  private resolvers: { resolve: (result?: any) => void, reject: (result?: any) => void }[] = [];
  private options: any;
  private currentAnimation: any;

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
      this.socket.onopen = function (e) {
        resolve(e);
      };
      this.socket.onerror = (e) => {
        reject(e);
      };
      this.socket.onmessage = (e) => {
        let payload = JSON.parse(e.data);
        this.resolvers[payload.id][payload.success ? 'resolve' : 'reject'](payload.payload);
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
    return this.send("getWifiInfo", {});
  }
}