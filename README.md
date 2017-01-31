# GeneratorPlotsAlt
Alternate GeneratorPlots which compiles easily as a precursor to histograms

This repository was created as a precursor to the histograms.  It's been tested to compile correctly.

PLEASE NOTE: the following files have been modified from the templates

1) MyxAODAnalysis.h

2) MyxAODAnalysis.cxx

3) Makefile.RootCore

4) PlotGeneratorQuantities.cxx

I tried to comment the stuff that I modified specifically with "GitHubProgramCode added."

I left in #include iostream and #include string in PlotGeneratorQuantities.cxx so I could see the "Hi" but commented it out of MyxAODAnalysis.cxx until I could figure out how to convert from ints to strings.  The single "Hi" can be deleted anytime; this was just a test so I could make sure it was compiling correctly and try and troubleshoot the not printing business.

To run the program, do the following after navigating to the working directory where you've cloned "GeneratorPlotsAlt:"

Open "MyAnalysis-->MyAnalysis-->util-->PlotGeneratorQuantities.cxx" in your favorite editor.

Change ExpandPathName to wherever you are (ending in .../GeneratorPlotsAlt) and save.

`bash`

`setupATLAS`

`lsetup 'rcSetup Base,2.4.14'`

`rc find_packages`

`rc compile`

`PlotGeneratorQuantities`

The output will be created in a folder called "SubmitDir" in the first "MyAnalysis" folder.

If you get any errors either in performing `rc find_packages` or `rc compile` then something went wrong somewhere along the way.

WARNING: If you attempt to rerun it without first deleting the "submitDir" folder, it'll throw an error!
