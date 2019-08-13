const HOST = 'http://192.168.1.58';
import * as $ from "jquery";
import 'jqueryui';

import appTemplate from './templates/app.twig';

const ANIMATIONS = {
    // static
    direct: {
        "DirectColorAnimation.speed": {type: "slider", options: {min: 1, max: 100}},
        "DirectColorAnimation.step": {type: "slider", options: {min: 1, max: 50}},
        "DirectColorAnimation.color.hue": {type: "slider", options: {min: 0, max: 360}},
        "DirectColorAnimation.color.sat": {type: "slider", options: {min: 0, max: 255}},
        "DirectColorAnimation.color.bright": {type: "slider", options: {min: 0, max: 255}},
    },
    dynamic: {
        "DynamicColorAnimation.speed": {type: "slider", options: {min: 0, max: 100}},
        "DynamicColorAnimation.color.sat": {type: "slider", options: {min: 0, max: 255}},
        "DynamicColorAnimation.color.bright": {type: "slider", options: {min: 0, max: 255}},
    },
    rainbow: {
        "RainbowAnimation.step": {type: "slider", options: {min: 0, max: 100}},
        "RainbowAnimation.period": {type: "slider", options: {min: 0, max: 100}},
        "RainbowAnimation.speed": {type: "slider", options: {min: 0, max: 100}},
        "RainbowAnimation.bright": {type: "slider", options: {min: 0, max: 255}},
    },
    strobe: {},
    dot_beat: {},
    blendwave: {},
    blur: {
        "BlurAnimation.bpm": {type: "slider", options: {min: 1, max: 255}},
        "BlurAnimation.bright": {type: "slider", options: {min: 0, max: 255}},
    },
    confetti: {
        "ConfettiAnimation.bright": {type: "slider", options: {min: 0, max: 255}},
    },
    // frequency
    frequency: {},
    frequency_strobe: {},
    frequency_running: {},
    spectrum: {},
    // uv
    uv: {},
};

function renderTemplate(template: (context: any) => string) {
    return template({ ANIMATIONS });
}

function renderUI() {
    document.body.innerHTML = renderTemplate(appTemplate);
}

function setAnimation(animation: string) {
    $.ajax(`${HOST}/api/v1/animation/`, {
        data: JSON.stringify({name: animation}),
        contentType: 'application/json',
        type: 'POST',
        success: () => {
        }
    });
}
function sendOption(animation: string, value: any) {
    console.log(value)
    return $.ajax(`${HOST}/api/v1/settings/`, {
        data: JSON.stringify({key: animation, value: value}),
        contentType: 'application/json',
        type: 'PUT',
        success: () => {
        }
    });
}

function bindUI() {
    document.querySelectorAll('[data-set-animation]').forEach((element: HTMLSelectElement) => {
        element.addEventListener('change', () => {
            const animation = element.value;
            setAnimation(animation)
        })
    });


    document.querySelectorAll('[data-slider]').forEach((slider: HTMLDivElement) => {
        let ajax;
        ($ as any)(slider).slider({
            min: slider.dataset.min ? parseInt(slider.dataset.min) : null,
            max: slider.dataset.max ? parseInt(slider.dataset.max) : null,
            slide: function( event, ui ) {
                console.log(ui);
                if (ajax) {
                    ajax.abort();
                }
                ajax = sendOption(slider.dataset.slider, ui.value)
            }
        });
    })
}

(function main() {
    renderUI();
    bindUI();
})();