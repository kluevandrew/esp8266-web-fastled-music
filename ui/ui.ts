import { Api } from "./api";
import { Renderer } from "./renderer";
import { ANIMATIONS } from "./config";
import * as noUiSlider from "nouislider";
import ReinventedColorWheel from "reinvented-color-wheel";


export class Ui {
  constructor(private api: Api, private renderer: Renderer) {
  }

  public init() {
    document.body.append(this.bind(this.renderer.render('app.html', {ANIMATIONS})));
    setImmediate(() => {
      const settingsSelector = document.querySelector<HTMLSelectElement>('[data-animation-selector]');
      settingsSelector.value = this.api.getCurrentAnimation();
      const settingsBlock = document.querySelector<HTMLDivElement>('[data-animation-settings]');
      settingsBlock.innerHTML = '';
      settingsBlock.append(this.bind(this.renderer.render(`animations/${this.api.getCurrentAnimation()}.html`, {animation: this.api.getCurrentAnimation()})));
    })
  }

  public bind(element: HTMLElement) {
    try {
      element.querySelectorAll('[data-animation-selector]').forEach((element: HTMLSelectElement) => {
        element.addEventListener('change', () => {
          this.setAnimation(element.value);
        })
      });

      element.querySelectorAll('[data-option-input]').forEach((optionInput: HTMLSelectElement) => {
        optionInput.addEventListener('change', () => {
          const value = parseInt(optionInput.value);
          this.api.setOption(optionInput.dataset.optionInput, value);
        });

        optionInput.value = this.api.getOption(optionInput.dataset.optionInput)
      });

      element.querySelectorAll('[data-save-settings]').forEach((element: HTMLSelectElement) => {
        element.addEventListener('click', () => {
          this.api.saveOptions().then(() => {
            alert("Настройки сохранены");
          });
        })
      });

      element.querySelectorAll('[data-reset-settings]').forEach((element: HTMLSelectElement) => {
        element.addEventListener('click', () => {
          if (confirm("Сбросить настройки?")) {
            this.api.resetOptions().then(() => {
              alert("Настройки сброшены");
            });
          }
        })
      });

      element.querySelectorAll('[data-slider]').forEach((slider: HTMLSelectElement) => {
        let value = this.api.getOption(slider.dataset.slider) || 0;

        let min;
        let max;
        let digits = parseInt(slider.dataset.float, 10);
        if (slider.dataset.float) {
          min = this.roundTo(parseFloat(slider.dataset.min), digits);
          max =  this.roundTo(parseFloat(slider.dataset.max), digits);
        } else {
          min = parseInt(slider.dataset.min, 10);
          max = parseInt(slider.dataset.max, 10);
        }

        noUiSlider.create(slider, {
          start: value,
          // step: slider.dataset.step ? parseFloat(slider.dataset.step) : 1,
          range: {
            'min': min,
            'max': max,
          },
          pips: {
            mode: 'steps',
            stepped: true,
            density: 5
          },
          tooltips: true,
          format: {
            from: (value) => {
              return slider.dataset.float ? this.roundTo(parseFloat(value), digits) : parseInt(value);
            },
            to: (value) => {
              return slider.dataset.float ? this.roundTo(parseFloat(value), digits) : parseInt(value);
            }
          },
        }).on('change.one', (values) => {
          let value = values[0];
          this.api.setOption(slider.dataset.slider, value);
        });
      });

      element.querySelectorAll('[data-color]').forEach((picker: HTMLSelectElement) => {
        const colorWheel = new ReinventedColorWheel({
          appendTo: picker,
          hsv: [
            Ui.map(this.api.getOption(`${picker.dataset.color}.hue`), 0, 255, 0, 360),
            Ui.map(this.api.getOption(`${picker.dataset.color}.sat`), 0, 255, 0, 100),
            Ui.map(this.api.getOption(`${picker.dataset.color}.bright`), 0, 255, 0, 100),
          ],
          wheelDiameter: 200,
          wheelThickness: 20,
          handleDiameter: 16,
          wheelReflectsSaturation: false,
          onChange: this.debounce((color) => {
            this.api.setColorOption(picker.dataset.color, color.hsv[0], color.hsv[1], color.hsv[2]);
          }, 200).bind(this),
        });
        setImmediate(colorWheel.redraw.bind(colorWheel), 0)
      });

      element.querySelectorAll('[data-toggle-addition-options]').forEach((button: HTMLButtonElement) => {
        button.addEventListener('click', () => {
          element.querySelectorAll('[data-toggle-addition-options]').forEach((e: HTMLButtonElement) => {
            e.classList.remove('btn--primary');
            e.classList.add('btn--default');
          });
          button.classList.add('btn--primary');
          button.classList.remove('btn--default');

          this.loadAdditionOptions(button.dataset.toggleAdditionOptions);
        })
      });
    } catch (e) {
      console.error(e)
    }

    return element;
  }

  public setAnimation(animation: string) {
    this.api.setAnimation(animation).then(() => {
      const settingsBlock = document.querySelector<HTMLDivElement>('[data-animation-settings]');
      settingsBlock.innerHTML = '';
      settingsBlock.append(this.bind(this.renderer.render(`animations/${animation}.html`, {animation: animation})));
    })
  }

  private debounce(func, delay) {
    let debounceTimer;
    return (function () {
      const context = this;
      const args = arguments;
      clearTimeout(debounceTimer);
      debounceTimer = setTimeout(() => func.apply(context, args), delay)
    });
  }

  private static map(x: number, inMin: number, inMax: number, outMin: number, outMax: number): number {
    const divisor = (inMax - inMin);
    if (divisor == 0) {
      return -1; //AVR returns -1, SAM returns 0
    }
    return (x - inMin) * (outMax - outMin) / divisor + outMin;
  }

  private roundTo(n, digits) {
    if (digits === undefined) {
      digits = 0;
    }

    const multiplicator = Math.pow(10, digits);
    n = parseFloat((n * multiplicator).toFixed(11));
    const test = (Math.round(n) / multiplicator);
    return +(test.toFixed(digits));
  }

  private loadAdditionOptions(type: string) {
    switch (type) {
       case 'wifi': this.loadWiFiOptions();
    }
  }

  private loadWiFiOptions() {
    this.api.getWifiNetworks().then((response) => {
      console.log(response);
    })
  }
}