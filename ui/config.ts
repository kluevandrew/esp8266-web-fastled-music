export const ANIMATIONS = {
  // static
  DirectColorAnimation: {
    key: "DirectColorAnimation",
    name: "Статичный цвет",
  },
  DynamicColorAnimation: {
    key: "DynamicColorAnimation",
    name: "Динамический цвет"
  },
  RainbowAnimation: {
    key: "RainbowAnimation",
    name: "Радуга"
  },
  StrobeAnimation: {
    key: "StrobeAnimation",
    name: "Стробосокоп",
  },
  DotBeatAnimation: {
    key: "DotBeatAnimation",
    name: "Точечный ритм",
  },
  BlendwaveAnimation: {
    key: "BlendwaveAnimation",
    name: "Смешанная волна",
  },
  BlurAnimation: {
    key: "BlurAnimation",
    name: "Пятна",
    options: {
      "BlurAnimation.bpm": {type: "slider", options: {min: 1, max: 255}},
      "BlurAnimation.bright": {type: "slider", options: {min: 0, max: 255}},
    },
  },
  ConfettiAnimation: {
    key: "ConfettiAnimation",
    name: "Конфетти",
    options: {
      "ConfettiAnimation.bright": {type: "slider", options: {min: 0, max: 255}},
    },
  },
  // frequency
  SimpleFrequencyAnimation: {
    key: "SimpleFrequencyAnimation",
    name: "Частоты",
  },
  FrequencyStrobeAnimation: {
    key: "FrequencyStrobeAnimation",
    name: "Частотный стробосокоп",
  },
  RunningFrequencyAnimation: {
    key: "RunningFrequencyAnimation",
    name: "Бегущие частоты",
  },
  SpectrumAnalyzerFrequencyAnimation: {
    key: "SpectrumAnalyzerFrequencyAnimation",
    name: "Анализатор спектра",
  },
  // uv
  // UvMeterAnimation: {
  //   key: "UvMeterAnimation",
  //   name: "UV-измеритель",
  // },
};
