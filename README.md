# raspimouse_cartographer

Configuration files for using [cartographer](http://wiki.ros.org/cartographer) with [Raspberry Pi Mouse](https://products.rt-net.jp/micromouse/en/raspberry-pi-mouse). 

# how to use

## install

Please run followings both on the robot and your PC.

```
$ cd catkin_ws/src/    #the src directory of your catkin workspace
$ git clone https://github.com/ryuichiueda/raspimouse_ros_2.git
$ rosdep install raspimouse_ros_2
$ git clone https://github.com/ryuichiueda/raspimouse_cartographer.git
$ rosdep install --ignore-src raspimouse_ros_2 raspimouse_cartographer
$ cd ~/catkin_ws/
$ catkin_make
```

## launch

Please edit `/etc/hosts` and host information on `launch/slam.launch` appropriately. Then, 

```
$ roslaunch raspimouse_cartographer slam.launch
```

## after finishing SLAM

Please push the front button. When the left side LED goes dark, the following files are saved:

* a map with the pgm format,
* some trajectory record files with the tsv format, and
* a bag file with the protocol buffer format.

After that, all of the nodes halt.

# acknowledgements

[Cartographer](http://wiki.ros.org/cartographer) is licensed under the Apache 2.0 license. 
