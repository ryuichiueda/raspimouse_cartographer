# raspimouse_cartographer

Configuration files for using [cartographer](http://wiki.ros.org/cartographer) with [Raspberry Pi Mouse](https://products.rt-net.jp/micromouse/en/raspberry-pi-mouse). 

# how to use

```
### robot side ###
$ roslaunch raspimouse_cartographer slam_remote_robot.launch
### PC side ###
$ roslaunch raspimouse_cartographer slam_remote_desktop.launch
$ rviz  <- do it on another terminal
```

# acknowledgements

[Cartographer](http://wiki.ros.org/cartographer) is licensed under the Apache 2.0 license. 
