function auto_program_linux(filename)
    % Get connected drives and their details
    drives = get_linux_drives();

    % Iterate through the drives
    for i = linspace(1,num_drives,num_drives)
        drive_path = drives{i}.mount_point;
        drive_name = drives{i}.name;

        % Check if the mount point ends with 'NOD_F411RE'
        if endsWith(drive_path, 'STLINK')
            disp("Found UCT_STLINK Drive: " + drive_name);

            % Copy the binary file to the drive
            copyfile([filename '.bin'], drive_path);

            pause(3); % Pause to ensure the file is copied
            disp("MicroMouse Programmed");
            STM32_ODR = 100;
            return;
        end
    end

    % If no STM32 drive is found, throw an error
    error("No MicroMouse Found");
end

function drives = get_linux_drives()
    % Executes Linux command to list block devices with mount points and names
    [status, cmdout] = system('lsblk -o NAME,MOUNTPOINT -n -p');

    if status ~= 0
        error("Failed to fetch drive information");
    end

    % Parse the command output
    drives = {};
    lines = strsplit(cmdout, '\n');
    for i = 1:length(lines)
        line = strtrim(lines{i});
        if isempty(line)
            continue;
        end

        % Split the line into NAME and MOUNTPOINT
        parts = strsplit(line);
        if length(parts) < 2
            continue; % Skip if mount point is not available
        end

        drives{end+1} = struct('name', parts{1}, 'mount_point', parts{2});
    end
end
