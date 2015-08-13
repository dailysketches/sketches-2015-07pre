Sketch 2015-06-01
--
This subfolder of the [sketches-2015-07pre repo](https://github.com/dailysketches/sketches-2015-07pre) is the root of an individual openFrameworks sketch. It contains the full source code used to generate this sketch:

[Listen to the sketch on Daily Sketches](http://dailysketches.github.io/sketch-01-06-2015/)

This source code is published automatically along with each sketch I add to [Daily Sketches](http://dailysketches.github.io).

Run this yourself
--
If you are running [openFrameworks via XCode](http://openframeworks.cc/download/) on a Mac you can just clone this directory and launch the `xcodeproj`. If you do that you should see something similar to the sketch above.

Addons
--
If the sketch uses any [addons](http://www.ofxaddons.com/unsorted) you don't already have you will have to clone them. Note that this readme was auto-generated and so doesn't list the addon dependencies. However you can figure out which addons you need pretty easily.

In XCode you will see a panel like this. Expand the folders under `addons` until you can see some of the source files underneath.

![How to find missing addon dependencies](https://github.com/dailysketches/dailySketches/blob/master/images/dependencies.png?raw=true)

In the example above, the addon `ofxLayerMask` is missing (it's source files are red), but `ofxGifEncoder` is present.

Versions
--
Note that openFrameworks doesn't have a great system for versioning addons. If you are getting results that look different to the gif above, or it won't compile, you may have cloned newer versions of some addons than were originally used to generate the sketch.

In that case you should clone the addon(s) at the most recent commit before the sketch date. Not ideal, but you will only have to do it rarely.

Yes, openFrameworks could use a good equivalent of [bundler](http://bundler.io/). You should write one!
