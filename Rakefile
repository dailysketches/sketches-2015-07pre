task :copy do
    copy_templates
    copy_sketches
    copy_gifs
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