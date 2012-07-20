/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
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

#include <Interface/Modules/Math/EvaluateLinearAlgebraUnaryDialog.h>
#include <Algorithms/Math/EvaluateLinearAlgebraUnary.h>
#include <Core/Dataflow/Network/ModuleStateInterface.h>  //TODO: extract into intermediate

using namespace SCIRun::Gui;
using namespace SCIRun::Domain::Networks;
using namespace SCIRun::Algorithms::Math;

EvaluateLinearAlgebraUnaryDialog::EvaluateLinearAlgebraUnaryDialog(const std::string& name, ModuleStateHandle state,
  QWidget* parent /* = 0 */)
  : ModuleDialogGeneric(parent),
  state_(state)
{
  setupUi(this);
  setWindowTitle(to_QString(name));
  executionTimeHorizontalSlider_->setValue(moduleExecutionTime());
  
  connect(executeButton_, SIGNAL(clicked()), this, SIGNAL(executeButtonPressed()));
  //connect(saveFileButton_, SIGNAL(clicked()), this, SLOT(saveFile()));
  connect(transposeRadioButton_, SIGNAL(clicked()), this, SLOT(pushOperationToState()));
  connect(negateRadioButton_, SIGNAL(clicked()), this, SLOT(pushOperationToState()));
  connect(scalarMultiplyRadioButton_, SIGNAL(clicked()), this, SLOT(pushOperationToState()));
  connect(scalarLineEdit_, SIGNAL(textChanged(const QString&)), this, SLOT(pushOperationToState(const QString&)));
}

int EvaluateLinearAlgebraUnaryDialog::moduleExecutionTime()
{
  return 2000;
}

int EvaluateLinearAlgebraUnaryDialog::getSelectedOperator() const
{
  if (transposeRadioButton_->isChecked())
    return (int)EvaluateLinearAlgebraUnaryAlgorithm::TRANSPOSE;
  if (negateRadioButton_->isChecked())
    return (int)EvaluateLinearAlgebraUnaryAlgorithm::NEGATE;
  if (scalarMultiplyRadioButton_->isChecked())
    return (int)EvaluateLinearAlgebraUnaryAlgorithm::SCALAR_MULTIPLY;
  else
    return -1;
}

void EvaluateLinearAlgebraUnaryDialog::pushOperationToState(const QString& str) 
{
  double value = str.toDouble();
  EvaluateLinearAlgebraUnaryAlgorithm::Operator op = (EvaluateLinearAlgebraUnaryAlgorithm::Operator) getSelectedOperator();

  state_->setValue("Operation", EvaluateLinearAlgebraUnaryAlgorithm::Parameters(op, value));
}

void EvaluateLinearAlgebraUnaryDialog::pushOperationToState()
{
  pushOperationToState("");
}