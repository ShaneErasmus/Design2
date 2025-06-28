function rtwpostbuildcallback()
% rtwpostbuildcallback - Run after Embedded Coder finishes build
% Uses pwd, removes _ert_rtw suffix, and finds ELF file in model folder

currentFolder = pwd;

% Remove trailing '_ert_rtw' from current folder name
pattern = '_ert_rtw';
modelFolder = regexprep(currentFolder, pattern, '');

% Extract model name from folder name (last part of path)
[~, modelName] = fileparts(modelFolder);

[parentFolder, ~, ~] = fileparts(currentFolder);
elfFile = string(modelName) + ".elf";

% Build full path to ELF file
elfFilePath = string(parentFolder) + '\' + string(modelName) + ".elf";

if ~exist(elfFilePath, 'file')
    disp(['Warning: ELF file not found at: ', elfFilePath]);
    return;
end

% Get size tool path
toolPath = matlabshared.supportpkg.getSupportPackageRoot;
exePath = fullfile(toolPath, '3P.instrset', 'gnuarm-armcortex.instrset', ...
    'win', 'bin', 'arm-none-eabi-size.exe');
exePath = strrep(exePath, '\', '/');
elfFilePath = strrep(elfFilePath, '\', '/');

% Memory limits (adjust as needed)
flash_max = 524288; % 512 KB
ram_max = 131072;   % 128 KB


disp('=== Memory Usage Summary ===');
disp(['ELF file: ', elfFile]);

% Run size command
command = sprintf('"%s" -A "%s"', exePath, elfFilePath);
[status, result] = system(command);

if status ~= 0
    disp(['Warning: Failed to run size command on: ', elfFilePath]);
    disp(['Error: ', result]);
    return;
end

% Parse result
lines = splitlines(string(result));
text = 0; data = 0; bss = 0;
for i = 1:numel(lines)
    line = strtrim(lines(i));
    if startsWith(line, '.text')
        parts = split(line);
        text = str2double(parts(2));
    elseif startsWith(line, '.data')
        parts = split(line);
        data = str2double(parts(2));
    elseif startsWith(line, '.bss')
        parts = split(line);
        bss = str2double(parts(2));
    end
end

flash = text + data;
ram = data + bss;

disp(sprintf('FLASH: %6d bytes (%.2f%% of 512 KB)', flash, 100 * flash / flash_max));
disp(sprintf('RAM:   %6d bytes (%.2f%% of 128 KB)', ram,   100 * ram / ram_max));
end
