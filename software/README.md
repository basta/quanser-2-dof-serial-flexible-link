# Software

`quanser_original` is the code that can be obtained on the dedicated page on [the product web](https://www.quanser.com/products/2-dof-serial-flexible-link/) page on Quanser website. Just for archiving purposes here. Do not use!

`quanser_updated` is the Quanser code after some modifications and upgrades useful or even necessary for our setup. In particular, the data acquisition board was set correctly to our `Q8 USB` DAQ, the configuration file `quanser_win64.tlc` for 64-bit Windows was correctly set, the Simulink files were saved in the new SLX format (corresponding to R2021a), the channels for reading digital inputs within the Limit Switches block were changed from `8:11` to `0:3`, and some irrelevant files (for the previous version of QUARC software) were removed for better clarity.
