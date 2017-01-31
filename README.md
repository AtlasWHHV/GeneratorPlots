# GeneratorPlotsAlt
Alternate GeneratorPlots which compiles easily as a precursor to histograms

This repository was created as a precursor to the histograms.  It's been tested to compile correctly.

PLEASE NOTE: the following files have been modified
1) MyxAODAnalysis.h
2) MyxAODAnalysis.cxx

To run the program, do the following after navigating to the working directory where you've cloned "GeneratorPlotsAlt:"

Open "MyAnalysis-->MyAnalysis-->util-->PlotGeneratorQuantities.cxx" in your favorite editor.

Change ExpandPathName to wherever you are (ending in .../GeneratorPlotsAlt) and save.

`bash`

`setupATLAS`

`lsetup 'rcSetup Base,2.4.14'`

`rc find_packages`

`rc compile`

`PlotGeneratorQuantities`

The output will be created in a folder called "SubDir" in the first "MyAnalysis" folder.

If you get any errors either in performing `rc find_packages` or `rc compile` then something went wrong somewhere along the way.
