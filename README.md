# GeneratorPlots
**To run the program, do the following:**

1) Add the line `source /phys/users/gwatts/bin/CommonScripts/configASetup.sh` to your .bashrc file in your home directory (this will setup the ATLAS files when you run bash).

2) Navigate to /phys/groups/tev/scratch4/users/nicolasNDS/GeneratorPlotsAltMast and copy the file DAOD_TRUTH0.5000_events_v2.pool.root and paste into your working directory. You should also add the line `export DATAPATH=[path-to-working-directory]` to your .bashrc file, where `[path-to-working-directory]` should be replaced with the path to your working directory. This variable points to the directory that stores the root file, and is used by PlotGeneratorQuantities.

3) Navigate to the working directory where you've cloned "GeneratorPlots" (do NOT cd into "GeneratorPlots").

4) Perform the following steps in the Terminal:

`bash`

`. GeneratorPlots/generate_plots.sh`

This script will install the necessary packages, compile the code, and run PlotGeneratorQuantities. Alternatively, you can do this manually by entering the following commands (in bash):

`lsetup 'rcSetup Base,2.4.14'`

`rc find_packages`

`rc compile`

`PlotGeneratorQuantities`

Either way, several different outputs will be created in a folder called "SubmitDir" in your working directory.

If you did everything correctly, in the Terminal you will see it print every 100 events from 0 to 500 so you know where you are.  You have to be a bit patient; your /hist and /input directories will not display until the program has finished running.

If you want to view more information, use the root command to look at the .root file(s) created in your submitDir. To view the created histograms, run the following commands in bash:

`root -l` (the -l indicates that the splash screen should not be displayed -- you may want to add `alias root='root -l'` to your .bashrc file, if you never want to see the splash screen)

`new TBrowser`

You should then see a browser with which you can navigate to the 'hist-[working-directory].root' file in the submitDir directory (replace `[working-directory]` with the name of your working directory). 

WARNING: If you attempt to rerun the program again without first deleting the "submitDir" folder, it'll throw an error! The script does this for you, but if you run it manually, keep this in mind.
