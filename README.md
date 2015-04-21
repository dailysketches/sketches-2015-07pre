What it does
--
Allows you to write sketches in openFrameworks, and:
- generate sketches as gifs
- automate the versioning and publishing of those gifs (in a jekyll repo)

Directory Structure
--
This repo's root dir must live alongside openFrameworks in a dir structure like this:

    /dailySketches (this repo's root dir)
        /dailysketches.github.io (jekyll repo root dir)
            /app
                /_posts (jekyll repo posts folder)
                /img
                    /sketches (gif files published here)
        /sketches
            /sketch1 (files will be copied to these dirs when you run 'rake copy')
            /sketch2 (this allows the code to be versioned in a single repo...)
            /etc
        /templates
            /sketchTemplate1
            /sketchTemplate2
            /etc
    /openFrameworks
        /versions
            /084 (root of an openFrameworks 084 instance)
                /dailySketches
                    /sketch1 (this is where you work making your sketches inside the OF dir)
                    /sketch2 (files are copied from these dirs... these files are not directly versioned)
                    /etc
                /dailySketchesTemplates
                    /sketchTemplate1
                    /sketchTemplate2
                    /etc

Usage
--
    rake copy

- force-copies everything from the openFrameworks template dirs into the dailySketches dir/repo