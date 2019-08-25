import { Api } from "./api";
import { Renderer } from "./renderer";
import { Ui } from "./ui";
import * as device from "../device.json";

(function main() {
  const HOST = ['127.0.0.1', 'localhost'].indexOf(document.location.hostname) > -1 ? device.ip : document.location.hostname;
  const api = new Api(HOST);

  const renderer = new Renderer();
  const ui = new Ui(api, renderer);
  ui.init();
  api.connect().then(() => {
    ui.hideLoader();
    ui.displayAnimationBlock(api.getCurrentAnimation());
  }).catch(() => {
    ui.showConnectionError();
  });

  api.onReConnect(() => {
    ui.hideConnectionError();
  });

  api.onError(() => {
    ui.showConnectionError();
  });
})();
