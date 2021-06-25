#pragma once

#include "Evaluation.h"
#include "RealConstraints.h"
#include "RealEvaluationInstances.h"

#include <RealEvaluationInstances.h>
#include <RealEvaluations.h>

using namespace System::Collections::Generic;

namespace EvaluationsCLI
{
	public ref class CRealEvaluation : public IEvaluation<double, double>
	{
	public:
		CRealEvaluation(Evaluations::IEvaluation<double, double> *pcNativeRealEvaluation);

		virtual ~CRealEvaluation();
		!CRealEvaluation();

		virtual double tEvaluate(IList<double> ^lSolution);

		virtual property int iSize
		{
			int get() { return pc_native_real_evaluation->iGetSize(); }
		}//virtual property int iSize

		virtual property double tMaxValue
		{
			double get() { return pc_native_real_evaluation->tGetMaxValue(); }
		}//virtual property double tMaxValue

		virtual property List<double>^ lOptimalParetoFront
		{
			List<double>^ get() { return l_optimal_pareto_front; }
		}//virtual property IList<double>^ lOptimalParetoFront

		virtual property ConstraintsCLI::IConstraint<double>^ pcConstraint
		{
			ConstraintsCLI::IConstraint<double>^ get() { return gcnew ConstraintsCLI::CRealConstraint(pc_native_real_evaluation->cGetConstraint()); }
		}//virtual property ConstraintsCLI::IConstraint<double>^ pcConstraint

		virtual property long long iFFE
		{
			long long get() { return pc_native_real_evaluation->iGetFFE(); }
		}//property long long iFFE

	protected:
		Evaluations::IEvaluation<double, double> *pc_native_real_evaluation;

	private:
		List<double>^ l_optimal_pareto_front;
	};//public ref class CRealEvaluation : public IEvaluation<double>


	public ref class CRealSphereEvaluation : public CRealEvaluation
	{
	public:
		CRealSphereEvaluation(int iSize);
	};//public ref class CRealSphereEvaluation : public CRealEvaluation


	public ref class CRealSphere10Evaluation : public CRealEvaluation
	{
	public:
		CRealSphere10Evaluation(int iSize);
	};//public ref class CRealSphere10Evaluation : public CRealEvaluation


	public ref class CRealEllipsoidEvaluation : public CRealEvaluation
	{
	public:
		CRealEllipsoidEvaluation(int iSize);
	};//public ref class CRealEllipsoidEvaluation : public CRealEvaluation


	public ref class CRealStep2SphereEvaluation : public CRealEvaluation
	{
	public:
		CRealStep2SphereEvaluation(int iSize);
	};//public ref class CRealStep2SphereEvaluation : public CRealEvaluation


	public ref class CRealRastriginEvaluation : public CRealEvaluation
	{
	public:
		CRealRastriginEvaluation(int iSize);
	};//public ref class CRealRastriginEvaluation : public CRealEvaluation


	public ref class CRealAckleyEvaluation : public CRealEvaluation
	{
	public:
		CRealAckleyEvaluation(int iSize);
	};//public ref class CRealAckleyEvaluation : public CRealEvaluation


	public ref class CRealCEC2013MultimodalEvaluation : public CRealEvaluation, public IMultimodalEvaluation<double>
	{
	public:
		CRealCEC2013MultimodalEvaluation(ERealCEC2013MultimodalInstance eInstance);

		virtual property int iNumberOfGlobalOptima
		{
			int get() { return (dynamic_cast<Evaluations::CRealCEC2013MultimodalEvaluation*>(pc_native_real_evaluation))->iGetNumberOfGlobalOptima(); }
		}//virtual property int iNumberOfGlobalOptima

		virtual property double dNicheRadius
		{
			double get() { return (dynamic_cast<Evaluations::CRealCEC2013MultimodalEvaluation*>(pc_native_real_evaluation))->dGetNicheRadius(); }
		}//virtual property double dNicheRadius
	};//public ref class CRealCEC2013MultimodalEvaluation : public CRealEvaluation, public IMultimodalEvaluation<double>
}//namespace EvaluationsCLI
