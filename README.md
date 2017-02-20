# STM32F4_DSP
Example of a series of bi-quad filters implemented on a STM32F4 microcontroller. 
This project implements a list of filters (LPF, BPF, APF, HPF, Notch) on an STM32F407VG microcontroller from STM32f4 Discovery board.
ADC is used to get samples, filtering is applied and outputed through the one of internal DACs.

A LCD DEM16216 is used to display a menu to select the Fs, Filter type and cuting frequency of the filter. The navigation through
menu is done using a rotary encoder.
