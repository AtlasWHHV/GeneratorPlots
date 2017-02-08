# GeneratorPlotsAlt

**HISTORY**

1) 20170128 Alternate GeneratorPlots which compiles easily as a precursor to creating and running steering macros.
2) 20170207 Alternate GeneratorPlots which compiles easily creating and running steering macros as a precursor to adding objects and tools for analysis.

**NOTES**

This repository has been tested to compile correctly.

PLEASE NOTE: the following files have been modified as of 20170207

1) PlotGeneratorQuantities.cxx

Some stuff that I modified originally is commented with "GitHubProgramCode added."

I left in "#include iostream" and "#include string" in PlotGeneratorQuantities.cxx so I could see the various "cout" print statements to know that the code was compiling up until that point and troubleshoot various issues (please see Issues n GitHub), but commented it out of MyxAODAnalysis.cxx until I could figure out how to convert from ints to strings.  These devices can be deleted at any time.

**To run the program, do the following:**

1) Navigate to /phys/groups/tev/scratch4/users/nicolasNDS/GeneratorPlotsAltMast and copy the file DAOD_TRUTH0.5000_events_v2.pool.root and paste into your working directory.

2) Navigate to the working directory where you've cloned "GeneratorPlotsAlt" (do NOT cd into "GeneratorPlotsAlt").

3) Perform the following steps in the Terminal:

`bash`

`setupATLAS`

`lsetup 'rcSetup Base,2.4.14'`

`rc find_packages`

`rc compile`

`PlotGeneratorQuantities`

Several different outputs will be created in a folder called "SubmitDir" in your working directory.

If you get any errors either in performing `rc find_packages` or `rc compile` then something went wrong somewhere along the way.

If you did everything correctly, in the Terminal you will see it print every 100 events from 0 to 500 so you know where you are.

If you want to view more information, use the root command to look at the .root file(s) created in your submitDir.

WARNING: If you attempt to rerun the program again without first deleting the "submitDir" folder, it'll throw an error!
