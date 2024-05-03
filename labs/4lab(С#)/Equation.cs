using MathNet.Symbolics;

public class Equation
{
    public Equation(string variable, SymbolicExpression expression)
    {
        Variable = variable;
        Expression = expression;
    }

    public SymbolicExpression GetDerivative()
    {
        return Expression.Differentiate(Variable);
    }

    public string Variable { get; set; }
    public SymbolicExpression Expression { get; set; }
}