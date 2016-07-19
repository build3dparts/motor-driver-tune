set flasher="%ProgramFiles(x86)%\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility\ST-LINK_CLI.exe"
set binary=Project\Output\Project.hex

%flasher% -c SWD -P %binary% 0x08000000 -V
