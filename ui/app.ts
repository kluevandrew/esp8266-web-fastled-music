import { Api } from "./api";
import { Renderer } from "./renderer";
import { Ui } from "./ui";

(function main() {
  const HOST = document.location.hostname === 'localhost' ? '192.168.1.58' : document.location.hostname;
  const api = new Api(HOST);

  const renderer = new Renderer();
  const ui = new Ui(api, renderer);
  api.connect().then(() => {
    ui.init();
  });
})();
