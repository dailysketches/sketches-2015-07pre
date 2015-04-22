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
	system 'cp -f sketches/*/bin/data/*.gif dailysketches.github.io/app/img/sketches/'
	system 'printf \'done.\n\''
end

def generate_posts
	system 'printf \'Generating posts... \''
	Dir.foreach 'dailysketches.github.io/app/img/sketches/' do |filename|
		if filename.end_with? '.gif'
			filename.slice! '.gif'
			generate_post filename
		end
	end
	system 'printf \'done.\n\''
end

def generate_post filename
	file = open("dailysketches.github.io/app/_posts/#{filename}-sketch.md", 'w')
	file.write('bla')
	file.close
end