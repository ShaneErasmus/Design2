function blkStruct = slblocks
% This function specifies that the library 'sendToUSB'
% should appear in the Library Browser with the 
% name 'Custom STM32 Blocks'

    Browser.Library = 'sendToUSB';
    % 'sendToUSB' is the name of the library

    Browser.Name = 'Custom STM32 Blocks';
    % 'Custom STM32 Blocks' is the library name that appears
    % in the Library Browser

    blkStruct.Browser = Browser;
    