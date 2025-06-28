% for IR_ADC High and Low Signal Processing
circularBufferSize = 25;

% for IR LEDs Pattern (fills the buffer nicely)
IR_LED_PERIOD = 0.2;

% for wheels
TIM3_ARR = 4000; % match STM32CubeMX

% for everything
samplingTime = -1;

% for encoders
wheelR = 32.5e-3;
axleLength = 12e-2;
ticksPerRot = 8;


modelName = 'newMicroMouseTemplate';  % Replace with your model name (no extension)

load_system(modelName);         % make sure the model is loaded


params = get_param(modelName, 'STM32');
fields = fieldnames(params);
disp(fields);