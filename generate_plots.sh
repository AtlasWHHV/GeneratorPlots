
# Load the default xAOD file if DATAPATH is not already configured.
if [ ! -v DATAPATH ]
then
  echo "DATAPATH not set, using default parameter."
  if [ ! -e ./DAOD_TRUTH0.5000_events_v2.pool.root ]
  then
    echo "xAOD file not found, copying from known location."
    cp /phys/groups/tev/scratch4/users/nicolasNDS/GeneratorPlotsAltMast/DAOD_TRUTH0.5000_events_v2.pool.root .
  fi
  export DATAPATH=.
fi

# Make sure ATLAS is configured.
if [ ! -v scriptLoc ]
then
  echo "It looks like configASetup has not been run. Running it now."
  source /phys/users/gwatts/bin/CommonScripts/configASetup.sh
fi

lsetup 'rcSetup Base,2.4.14'
rc find_packages
rc compile
rm -rf submitDir/
PlotGeneratorQuantities
