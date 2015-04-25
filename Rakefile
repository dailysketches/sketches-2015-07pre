task :copy do
	copy_templates
	copy_sketches
	copy_gifs
	generate_posts
end

def copy_templates
	system 'printf \'Copying templates... \''
	system 'cp -rf ../openFrameworks/versions/084/apps/dailySketchesTemplates/ templates'
	system 'printf \'done.\n\''
end

def copy_sketches
	system 'printf \'Copying sketches... \''
	system 'cp -rf ../openFrameworks/versions/084/apps/dailySketches/ sketches'
	system 'printf \'done.\n\''
end

def copy_gifs
	system 'printf \'Copying GIFs... \''
	system 'cp -f sketches/*/bin/data/*.gif dailysketches.github.io/app/sketches/openFrameworks/'
	system 'printf \'done.\n\''
end

def generate_posts
	system 'printf \'Generating posts... \''
	Dir.foreach 'dailysketches.github.io/app/sketches/openFrameworks/' do |filename|
		if filename.end_with? '.gif'
			filename.slice! '.gif'
			generate_post filename
		end
	end
	system 'printf \'done.\n\''
end

def generate_post filename
	filepath = "dailysketches.github.io/app/_posts/#{filename}-sketch.md"
	unless File.exist?(filepath)
		file = open(filepath, 'w')
		file.write(file_contents filename)
		file.close
	end
end

def file_contents datestring
	<<-eos
---
layout: post
title:  "Sketch #{datestring}"
date:   #{datestring}
---
![Daily sketch](/sketches/openFrameworks/#{datestring}.gif)
<div class="code">
	<ul>
		<li><a href="{% post_url #{datestring}-sketch %}">permalink</a></li>
		<li><a href="https://github.com/dailysketches/dailySketches/tree/master/sketches/#{datestring}">code</a></li>
		<li><a href="#" class="snippet-button">snippet</a></li>
	</ul>
	<p>Description here</p>
	<pre class="snippet">
		<code class="cpp">Your code here</code>
	</pre>
</div>
eos
end