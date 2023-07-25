# Cubit-CalculiX
Hey ho that´s the CalculiX Component for coreform cubit!

Full Model definitions for CalculiX can be done with Cubit as Preprocessor.

Here you can find the source code and a build for linux.
If you want to build the component yourself, i would recommend using Centos 7.
As far as i know, that's the distro on which cubit is build.

This component was build for Cubit 2022.4! 

Tested with Cubit 2022.4 on Ubuntu 22.04

# Key Features
Definition of:
- Elements Sets
- Node Sets
- Side Sets
- Materials (Conductivity, Density, Elastic, Expansion, Plastic, Specific Heat)
- Sections (Solid, Shell, Membrane, Beam)
- Constraints (Tie, Rigid Body)
- Surface Interactions
- Contact Pairs
- Amplitudes
- Loads (CLOAD, DLOAD, DFLUX, GRAVITY, CENTRIF)
- Boundary Conditions (Displacements, Temperatures)
- Initial Conditions (Displacements, Temperatures)
- History Outputs (NODE PRINT, EL PRINT, CONTACT PRINT)
- Field Outputs (NODE FILE, EL FILE, CONTACT FILE)
- STEPS (Static, Frequency, Buckle, Heat Transfer, Coupled Temperature Displacement, Uncoupled Temperature Displacement, No Analysis)
- Creation and Running of Jobs
- Opening of Results with CGX or Paraview
- Adding Customlines before/after Keywords

- Export of Calculix Model

# Installation

Download the build directory and point within Cubit to the Direcetory.

- Tools->Plugins->Add

Restart Cubit.

The Cubit Window should now show "Coreform Cubit 2022.4 -- with CalculiX" in the Title.

- Tools->Options->CalculiX

Now you have fill in the Paths to CCX, CGX, Paraview, ccx2paraview, the icons from the build and give a number for the wanted threads for the solver.

Restart Cubit.

Enable Model Tree

- View->CalculiX Model Tree

Try to open and run the journal file "first_run.jou"



# todo list
- documentation
- *.dat file reader
