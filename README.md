# monte-carlo-xcel

This is a project for ECE 6775 - High-Level Digital Design Automation - at Cornell University. It uses HLS to accelerating Monte Carlo Based Options Pricing. The ecelinux folder contains a Vivado HLS project to synthesize the monte carlo hardware module. The zedboard contains a C++ project to build the monte carlo host program which can then be run on the zedboard after programming the FPGA with this code. 

## To run this design on the ARM simulator
1. Navigate to the ecelinux folder within this repository.
2. Run `vivado_hls -f run.tcl`

## To run this design on the zedboard
1. Run `vivado_hls -f run.tcl` to generate Verilog for this moduel 
2. Run `source run_bitstream.sh` to generate the bitstream that will be used to reconfigure the FPGA 
3. Scp the generated `xillydemo.bit` to the zedboard using `scp xillydemo.bit <user>@zhang-zedboard-xx.ece.cornell.edu:~`
4. Login to the zedboard - `ssh <user>@zhang-zedboard-xx.ece.cornell.edu`
5. Run `mount /mnt/sd` to mount the SD card
6. Run `cp xillydemo.bit /mnt/sd`
7. Run `sudo reboot` so these changes take effect
8. Scp this whole monte-carlo folder to the zedboard that was just reprogrammed using `scp /path-to-zip/monte-carlo.zip <user>@zhang-zedboard-xx.ece.cornell.edu:`
9. After unzipping the folder, navigate to the zedboard folder and run `make fpga` 


Collaborators - Angela Cui, Andrew Cheng, Eshita Sangani, Evan Williams
