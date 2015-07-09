require 'date' 

$current_asset_dir = 'sketches-2015-04-22'

#api
task :copy do
	copy_templates
	copy_sketches
	copy_media
	generate_files
end

#tasks
def copy_templates
	system 'printf \'Copying templates... \''
	system 'rsync -ru ../openFrameworks/versions/084/apps/dailySketchesTemplates/ templates'
	system 'printf \'done.\n\''
end

def copy_sketches
	system 'printf \'Copying sketches... \''
	system 'rsync -ru ../openFrameworks/versions/084/apps/dailySketches/ sketches'
	system 'printf \'done.\n\''
end

def copy_media
	system 'printf \'Copying generated sketch media... \''
	system "mv -f sketches/*/bin/data/out/* assets/#$current_asset_dir/openFrameworks/"
	system 'printf \'done.\n\''
end

def generate_files
	system 'printf \'Generating files... \''
	Dir.foreach "assets/#$current_asset_dir/openFrameworks/" do |filename|
		if filename.end_with? '.gif'
			filename.slice! '.gif'
			generate_post filename, 'gif'
			generate_readme filename, 'gif'
		end
		if filename.end_with? '.mp3'
			filename.slice! '.mp3'
			generate_post filename, 'mp3'
			generate_readme filename, 'mp3'
		end
	end
	system 'printf \'done.\n\''
end

def generate_post datestring, ext
	filepath = "dailysketches.github.io/app/_posts/#{datestring}-sketch.md"
	unless File.exist?(filepath)
		file = open(filepath, 'w')
		file.write(post_file_contents datestring, ext)
		file.close
	end
end

def generate_readme datestring, ext
	filepath = "sketches/#{datestring}/README.md"
	unless File.exist?(filepath)
		file = open(filepath, 'w')
		file.write(readme_file_contents datestring, ext)
		file.close
	end
end

#string builders
def post_file_contents datestring, ext
	<<-eos
---
layout: post
title:  "Sketch #{datestring}"
date:   #{datestring}
---
<div class="code">
    <ul>
		<li><a href="{% post_url #{datestring}-sketch %}">permalink</a></li>
		<li><a href="https://github.com/dailysketches/dailySketches/tree/master/sketches/#{datestring}">code</a></li>
		<li><a href="#" class="snippet-button">snippet</a></li>
	</ul>
    <pre class="snippet">
        <code class="cpp">Your code here</code>
    </pre>
</div>
<p class="description">Description here</p>
#{ext == 'gif' ? render_post_gif(datestring) : render_post_mp3(datestring)}
eos
end

def readme_file_contents datestring, ext
	<<-eos
Sketch #{datestring}
--
This subfolder of the [dailySketches repo](https://github.com/dailysketches/dailySketches) is the root of an individual openFrameworks sketch. It contains the full source code used to generate this sketch:

#{ext == 'gif' ? render_readme_gif(datestring) : render_readme_mp3(datestring)}

This source code is published automatically along with each sketch I add to [Daily Sketches](http://dailysketches.github.io). Here is a [permalink to this sketch](http://dailysketches.github.io/sketch-#{reverse datestring}/) on the Daily Sketches site.

Run this yourself
--
If you are running [openFrameworks via XCode](http://openframeworks.cc/download/) on a Mac you can just clone this directory and launch the `xcodeproj`. If you do that you should see something similar to the sketch above.

Addons
--
If the sketch uses any [addons](http://www.ofxaddons.com/unsorted) you don't already have you will have to clone them. Note that this readme was auto-generated and so doesn't list the addon dependencies. However you can figure out which addons you need pretty easily.

In XCode you will see a panel like this. Expand the folders under `addons` until you can see some of the source files underneath.

![How to find missing addon dependencies](../../images/dependencies.png)

In the example above, the addon `ofxLayerMask` is missing (it's source files are red), but `ofxGifEncoder` is present.

Versions
--
Note that openFrameworks doesn't have a great system for versioning addons. If you are getting results that look different to the gif above, or it won't compile, you may have cloned newer versions of some addons than were originally used to generate the sketch.

In that case you should clone the addon(s) at the most recent commit before the sketch date. Not ideal, but you will only have to do it rarely.

Yes, openFrameworks could use a good equivalent of [bundler](http://bundler.io/). You should write one!
eos
end

#string builder helpers
def reverse datestring
	date = DateTime.parse(datestring)
	date.strftime('%d-%m-%Y')
end

def raw_url datestring, ext
	"https://github.com/dailysketches/#$current_asset_dir/blob/master/openFrameworks/#{datestring}.#{ext}?raw=true"
end

def render_post_gif datestring
	"![Daily sketch](#{raw_url datestring, 'gif'})"
end

def render_post_mp3 datestring
	<<-eos
![Sketch #{datestring}](#{raw_url datestring, 'png'})
<audio controls>
	<source src="#{raw_url datestring, 'mp3'}" type="audio/mpeg">
	Your browser does not support the audio element.
</audio>
eos
end

def render_readme_gif datestring
	"![Sketch #{datestring}](#{raw_url datestring, 'gif'})"
end

def render_readme_mp3 datestring
	<<-eos
![Sketch #{datestring}](#{raw_url datestring, 'png'})
[Listen to the sketch on Daily Sketches](http://dailysketches.github.io/sketch-#{reverse datestring}/)"
eos
end