========================================================================
    OpenCL_x86_test Project Overview
========================================================================

This application propose binarization with OpenCL kernel
as a simplest demonstration of zLayersLib architecture formalization facilities.

There are 3 Abstract layers:
1)BitmapToVectorLayer convetrs bitmap file to vector.
2)SimpleOpenCLLayer uses data from previous layer and processes it with OpenCL kernel
3)VectorToBitmapLayer saves processed data back to file.

Before run, make sure that OpenCL drivers was installed on your computer.