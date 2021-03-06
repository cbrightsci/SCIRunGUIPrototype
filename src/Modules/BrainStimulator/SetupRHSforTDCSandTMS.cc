/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
   University of Utah.

   
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <Modules/BrainStimulator/SetupRHSforTDCSandTMS.h>
#include <Core/Algorithms/BrainStimulator/SetupRHSforTDCSandTMSAlgorithm.h>
#include <Core/Datatypes/Legacy/Field/Field.h>
#include <Core/Algorithms/Base/AlgorithmPreconditions.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/MatrixTypeConversions.h>
#include <vector>

using namespace SCIRun::Modules::BrainStimulator;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms::BrainStimulator;
using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Dataflow::Networks;

SetupRHSforTDCSandTMSModule::SetupRHSforTDCSandTMSModule() : Module(ModuleLookupInfo("SetupRHSforTDCSandTMS", "BrainStimulator", "SCIRun"))
{
 INITIALIZE_PORT(MESH);
 INITIALIZE_PORT(SCALP_TRI_SURF_MESH);
 INITIALIZE_PORT(ELECTRODE_TRI_SURF_MESH);
 INITIALIZE_PORT(ELECTRODE_SPONGE_LOCATION_AVR);
 INITIALIZE_PORT(LHS_KNOWNS);
 INITIALIZE_PORT(ELECTRODE_ELEMENT);
 INITIALIZE_PORT(ELECTRODE_ELEMENT_TYPE);
 INITIALIZE_PORT(ELECTRODE_ELEMENT_DEFINITION);
 INITIALIZE_PORT(ELECTRODE_CONTACT_IMPEDANCE);
 INITIALIZE_PORT(RHS);
 INITIALIZE_PORT(ELECTRODE_SPONGE_SURF);
 INITIALIZE_PORT(SELECTMATRIXINDECES);
}

void SetupRHSforTDCSandTMSModule::setStateDefaults()
{
  auto state = get_state();
  setStateIntFromAlgo(Parameters::refnode);
  setStateDoubleFromAlgo(Parameters::normal_dot_product_bound);
  setStateDoubleFromAlgo(Parameters::pointdistancebound);
  setStateIntFromAlgo(Parameters::number_of_electrodes);
}

void SetupRHSforTDCSandTMSModule::execute()
{ 
  auto mesh = getRequiredInput(MESH);
  auto scalp_tri_surf = getRequiredInput(SCALP_TRI_SURF_MESH);
  auto elc_tri_surf = getRequiredInput(ELECTRODE_TRI_SURF_MESH);
    
  DenseMatrixHandle elc_sponge_location = matrix_convert::to_dense(getRequiredInput(ELECTRODE_SPONGE_LOCATION_AVR));
  
  // obtaining electrode values from state map
  auto elc_vals_from_state = get_state()->getValue(Parameters::ElectrodeTableValues).toVector();
  algo().set(Parameters::ELECTRODE_VALUES, elc_vals_from_state);
  
  auto imp_vals_from_state = get_state()->getValue(Parameters::ImpedanceTableValues).toVector();
  algo().set(Parameters::IMPEDANCE_VALUES, imp_vals_from_state);
 
  if (needToExecute())
  {
    update_state(Executing);
    auto state = get_state();
    state->setValue(Parameters::refnode, get_state()->getValue(Parameters::refnode).toInt());
    state->setValue(Parameters::normal_dot_product_bound, get_state()->getValue(Parameters::normal_dot_product_bound).toDouble());
    state->setValue(Parameters::pointdistancebound, get_state()->getValue(Parameters::pointdistancebound).toDouble());
        
    int nr_elec=elc_sponge_location->nrows(); /// get the number of electrodes in the first execution to update the GUI
    if (elc_sponge_location && nr_elec>=2)
    {
     state->setValue(Parameters::number_of_electrodes, nr_elec);
    }
    
    auto output = algo().run_generic(make_input((MESH, mesh)(SCALP_TRI_SURF_MESH, scalp_tri_surf)(ELECTRODE_TRI_SURF_MESH, elc_tri_surf)(ELECTRODE_SPONGE_LOCATION_AVR, elc_sponge_location)));
    sendOutputFromAlgorithm(LHS_KNOWNS, output);
    sendOutputFromAlgorithm(ELECTRODE_ELEMENT, output);
    sendOutputFromAlgorithm(ELECTRODE_ELEMENT_TYPE, output);
    sendOutputFromAlgorithm(ELECTRODE_ELEMENT_DEFINITION, output);
    sendOutputFromAlgorithm(ELECTRODE_CONTACT_IMPEDANCE, output);
    sendOutputFromAlgorithm(RHS, output);
    sendOutputFromAlgorithm(ELECTRODE_SPONGE_SURF, output);
    sendOutputFromAlgorithm(SELECTMATRIXINDECES, output);
  }
}
