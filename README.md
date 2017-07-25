# GeneratorPlots
**To run the program, do the following:**

1) Add the line `source /phys/users/gwatts/bin/CommonScripts/configASetup.sh` to your .bashrc file in your home directory (this will setup the ATLAS files when you run bash). If you don't do this, the script will do it for you, but it's a good idea to do it anyway.

2) If you have a particular xAOD file in mind, add `export DATAPATH=[path-to-file]` to your .bashrc file, where `[path-to-file]` should be replaced with the path to the directory in which your xAOD file is stored. If you do not set DATAPATH, the script will use a default xAOD file.

3) Navigate to the working directory where you've cloned "GeneratorPlots" (do NOT cd into "GeneratorPlots").

4) Perform the following steps in the Terminal:

`bash`

`. GeneratorPlots/generate_plots.sh`

This script will install the necessary packages, compile the code, and run PlotGeneratorQuantities. Several different outputs will be created in a folder called "SubmitDir" in your working directory.

If you did everything correctly, in the Terminal you will see it print every 100 events from 0 to 500 so you know where you are.  You have to be a bit patient; your /hist and /input directories will not display until the program has finished running.

If you want to view more information, use the root command to look at the .root file(s) created in your submitDir. To view the created histograms, run the following commands in bash:

`root -l` (the -l indicates that the splash screen should not be displayed -- you may want to add `alias root='root -l'` to your .bashrc file, if you never want to see the splash screen)

`new TBrowser`

You should then see a browser with which you can navigate to the 'hist-[working-directory].root' file in the submitDir directory (replace `[working-directory]` with the name of your working directory). 
