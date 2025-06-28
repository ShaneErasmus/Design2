classdef CustomSerialSend < matlab.System
    % SerialSendObj = src.CustomSerialSend
    % creates a Custom Serial Send system object.
    
    % Copyright 2020-2023 The MathWorks, Inc.
    
    % Public, non-tunable properties
    properties(Nontunable)
        % Communication port
        PortSel = '<Select a port...>'
        Header double;
        Terminator = '<none>'
        % Custom terminator
        CustomTerminator double;
        ComPort = '<Select a port...>';
    
        % Enable blocking mode
        EnableBlockingMode (1, 1) logical = true
    end
    
    properties (Hidden)
        TerminatorSet = matlab.system.StringSet(cellstr(["<none>", "CR ('\r')", "LF ('\n')", "CR/LF ('\r\n')", "NULL ('\0')", "Custom terminator"]))
    end
    
    %#codegen
    properties (Access = 'private')
        SerialObj
    end
    
    methods
        %% Constructor
        function obj = CustomSerialSend(varargin)
            % Support name-value pair arguments when constructing object
            setProperties(obj, nargin, varargin{:})
        end
        
        %% Set functions to validate and set the property value.
        function set.CustomTerminator(obj, value)
            if ~isempty(value)
                validateattributes(value, {'numeric'}, ...
                    { '>=', 0, '<=', 255, 'real', 'nonnan', 'integer', 'row'}, ...
                    '', 'Terminator')
            end
            obj.CustomTerminator = value;
        end
        
        function set.Header(obj, value)
            if ~isempty(value)
                validateattributes(value, {'numeric'}, ...
                    { '>=', 0, '<=', 255, 'real', 'nonnan', 'integer', 'row'}, ...
                    '', 'Header')
            end
            obj.Header = value;
        end
    end
    
    methods(Access = protected)
        %% Define number of inputs and outputs to the system.
        function num = getNumOutputsImpl(~)
            % Define total number of outputs for system.
            num = 0;
        end
        
    end
    
    methods(Access = protected)
        %% Algorithm implementation
function stepImpl(obj, input)
            if isempty(input)
                return;
            end

            TerminatorVal = uint8(obj.CustomTerminator);
            if ~strcmpi(obj.Terminator, 'Custom Terminator')
                switch obj.Terminator
                    case {"CR ('\r')", "LF ('\n')", "CR/LF ('\r\n')", "NULL ('\0')"}
                        index = strfind(obj.Terminator, '(');
                        if ~isempty(index)
                            TerminatorVal = uint8(sprintf(obj.Terminator(index+2 : end-2)));
                        end
                    otherwise
                        if isempty(obj.Terminator) || strcmpi(obj.Terminator, '<none>')
                            TerminatorVal = uint8([]);
                        end
                end
            end

            rowInput = reshape(input, [1 numel(input)]);
            inputval = typecast(rowInput, 'uint8');
            data = [uint8(obj.Header) inputval TerminatorVal];

            try
                if obj.EnableBlockingMode
                    obj.SerialObj.write(data);
                else
                    obj.SerialObj.writeAsync(data);
                end
            catch
                disp("MicroMouse Disconnected, attempting to reconnect...");
                success = false;
                tStart = tic;
                timeout = 5; % seconds

                while toc(tStart) < timeout && ~success
                    try
                        obj.SerialObj.disconnect;
                    catch
                    end
                    try
                        obj.SerialObj.connect;
                        % Retry the write
                        if obj.EnableBlockingMode
                            obj.SerialObj.write(data);
                        else
                            obj.SerialObj.writeAsync(data);
                        end
                        success = true;
                        disp("Reconnected successfully.");
                    catch
                        pause(0.2); % wait a bit before retrying
                    end
                end

                if ~success
                    error("MicroMouse communication timeout after 5 seconds.");
                end
            end
        end
    
        function setupImpl(obj)
            if strcmpi(obj.PortSel, '<Select a port...>')
                coder.internal.error('instrument:instrumentblks:noPortsSelected');
            end

            % Check if the parameter value is a variable. If yes, resolve
            % the variable and use its value. If parameter value is an
            % existing serial port, do not resolve.
            portValue = obj.PortSel;
            % Use coder.extrinsic to call the function in MATLAB rather than generating
            %code for it. This is done for functions that doesnt support codegen.
            coder.extrinsic('serialportlist');
            coder.extrinsic('slResolve');
            coder.extrinsic('gcb');
            coder.extrinsic('ismember');
            % Use coder.const to evaluate function call at compile time instead of run time.
            blockPath = coder.const(gcb);
            slList = coder.const(serialportlist);
            portInList = coder.const(~ismember(obj.PortSel, slList));
            if portInList
                [portValue, portStatus]= coder.const(@slResolve,obj.PortSel, blockPath);
                if ~portStatus
                    portValue = obj.PortSel;
                end
            end

            obj.SerialObj = matlabshared.seriallib.internal.Serial(portValue, 'IsSharingPort', true, ...
                'IsSharingExistingTimeout', true, 'IsWriteOnly', true);
            obj.SerialObj.WriteAsync = ~obj.EnableBlockingMode;
            obj.SerialObj.connect;
            % Check if the Serial object has initiaization access. If yes, the port
            % was not configured by the Serial object created in Serial configuration system object.
            if obj.SerialObj.InitAccess
                coder.internal.error('instrument:instrumentblks:portNotConfigured');
            end
        end
        
        function releaseImpl(obj)
            % Release resources, such as file handles
            obj.SerialObj.disconnect;
        end
        
        function validatePropertiesImpl(~)
            % Validate related or interdependent property values
            %@TODO investigate if preApply type check needed here
        end
        
        function validateInputsImpl(~, input)
            validateattributes(input, {'double', 'single', 'int8', 'uint8', ...
                'int16', 'uint16', 'int32', 'uint32'}, {})
        end
        
        function num = getNumInputsImpl(~)
            % Define total number of inputs for system with optional inputs
            num = 1;
        end
        
    end
end
