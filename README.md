# TruthNtuple
Generator level ntuplizer for CMSSW

## Setup

Set up CMSSW, then run

```
git clone git@github.com:clelange/TruthNtuple.git Analysis/TruthNtuple
scram b
```

## Additional scripts and configs

There are a couple of helper scripts in the [scripts](scripts) directory:

### Crab submission and generator fragments

Some generator fragments can be found in [genproduction_configs](genproduction_configs). These need to be copied to `${CMSSW_BASE}/src/Configuration/GenProduction/python/`. Then [createConfigs.sh](scripts/createConfigs.sh) can be used to create configs that can be executed using `cmsRun`. The configs will end up in a directory called `config`.

These configs can also be used for crab job submission:

```
source /cvmfs/cms.cern.ch/crab3/crab.sh
```

The template [crabConfig.py](scripts/crabConfig.py) is used by [submitCrab.sh](scripts/submitCrab.sh), which loops over the config files in the `config` directory.

### Ntuple generation

There are two scripts to facilitate running over the newly generated ([createNtuple.sh](scripts/createNtuple.sh)) or centrally produced ([createNtuple_DAS.sh](scripts/createNtuple_DAS.sh)). They basically just take care of creating a list of comma-separated files that the ntuplizer then uses as input.

## Plotting

There are a couple of plot scripts in the [plotting](plotting) directory:

### [plotdjr.py](plotting/plotdjr.py)

Script to determine qCut values for samples produced using MLM matching.

### [plotVqq.py](plotting/plotVqq.py)

The script uses the ([plots.ini](plotting/plots.ini)) file as config.
