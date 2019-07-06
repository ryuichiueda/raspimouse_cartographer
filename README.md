# raspimouse_cartographer

Configuration files for using [cartographer](http://wiki.ros.org/cartographer) with [Raspberry Pi Mouse](https://products.rt-net.jp/micromouse/en/raspberry-pi-mouse). 

# how to use

Please install required package. (I should list them here but not yet.)

## launch

```
$ roslaunch raspimouse_cartographer slam.launch
```

## after finishing SLAM

Please push the front button. When the left side LED goes dark, the following files are saved:

* a map with the pgm format,
* a trajectory record with the tsv format, and
* a bag file with the protocol buffer format.

# acknowledgements

[Cartographer](http://wiki.ros.org/cartographer) is licensed under the Apache 2.0 license. 
