using _4lab;
using MathNet.Symbolics;

List<List<SymbolicExpression>> GetDerivativeMatrix(List<List<Equation>> matrix)
{
    List<List<SymbolicExpression>> derivativeMatrix = new List<List<SymbolicExpression>>();

    IDictionary<string, FloatingPoint> dict = new Dictionary<string, FloatingPoint>
            {
                { "x", 5 },
                { "y", 5 }
            };

    foreach (var line in matrix)
    {
        List<SymbolicExpression> derivativeLine = [];
        foreach(var equation in line)
        {
            derivativeLine.Add(equation.GetDerivative());
        }
        derivativeMatrix.Add(derivativeLine);
    }

    for (int i = 0; i < derivativeMatrix.Count; i++)
    {
        bool isAllZeroInRow = true;
        for (int j = 0; j < derivativeMatrix[i].Count; j++)
        {
            if (derivativeMatrix[j][i].Evaluate(dict).RealValue != 0)
            {
                isAllZeroInRow = false;
                break;
            }
        }

        if (isAllZeroInRow)
        {
            derivativeMatrix.RemoveAt(i);
            i--;
        }
    }

    int columnCount = derivativeMatrix[0].Count;

    for (int i = 0; i < columnCount; i++)
    {
        bool isAllZeroInColumn = true;
        for (int j = 0; j < derivativeMatrix.Count; j++)
        {
            if (derivativeMatrix[j][i].Evaluate(dict).RealValue != 0)
            {
                isAllZeroInColumn = false;
                break;
            }
        }

        if (isAllZeroInColumn)
        {
            for (int j = 0; j < derivativeMatrix.Count; j++)
            {
                derivativeMatrix[j].RemoveAt(i);
            }
            // i-- ???
        }
    }

    return derivativeMatrix;
}

List<List<double>> GetJacobMatrix(List<List<SymbolicExpression>> derivativeMatrix, State state)
{
    List<List<double>> jacobMatrix = [];

    IDictionary<string, FloatingPoint> dict = new Dictionary<string, FloatingPoint>
            {
                { "x", state.X },
                { "y", state.Y }
            };

    for (int i = 0; i < derivativeMatrix.Count; i++)
    {
        List<double> jacobLine = [];
        for (int j = 0; j < derivativeMatrix[i].Count; j++)
        {
            jacobLine.Add(derivativeMatrix[i][j].Evaluate(dict).RealValue);
        }
        jacobMatrix.Add(jacobLine);
    }

    return jacobMatrix;
}

List<double> GetResults(List<List<Equation>> matrix, State state)
{
    List<double> result = [];
    IDictionary<string, FloatingPoint> dict = new Dictionary<string, FloatingPoint>
            {
                { "x", state.X },
                { "y", state.Y }
            };

    for (int i = 0; i < matrix.Count; i++)
    {
        double sum = 0;
        for (int j = 0; j < matrix[i].Count; j++)
        {
            if (j > 0 && matrix[i][j].Expression.ToString().Equals(matrix[i][j - 1].Expression.ToString()))
                continue;
            sum += matrix[i][j].Expression.Evaluate(dict).RealValue;
        }
        result.Add(sum);
    }

    return result;
}

double GetDeterminate(List<List<double>> matrix, List<double> result)
{
    double prod = 1;

    for (int i = 0; i < matrix.Count; i++)
    {
        prod *= matrix[i][i];
    }

    double secondProd = 1;
    for (int i = matrix.Count - 1; i >= 0; i--)
    {
        secondProd *= matrix[i][matrix[i].Count - i - 1];
    }

    return prod - secondProd;
}

List<List<double>> GetMinor(List<List<double>> matrix)
{
    List<List<double>> result = new List<List<double>>(matrix.Count);
    for (int i = 0; i < matrix.Count; i++)
    {
        List<double> row = new List<double>(matrix[i].Count);
        for (int j = 0; j < matrix[i].Count; j++)
        {
            row.Add(0);
        }
        result.Add(row);
    }

    for (int i = 0; i < matrix.Count; i++)
    {
        for (int j = 0; j < matrix[i].Count; j++)
        {
            int k = i;
            int m = j;
            if (i % 2 == 0 && j % 2 == 0) { k++; m++; }
            else if (i % 2 == 0 && j % 2 != 0) { k++; m--; }
            else if (i % 2 != 0 && j % 2 == 0) { k--; m++; }
            else if (i % 2 != 0 && j % 2 != 0) { k--; m--; }

            result[i][j] = matrix[k][m];

            if ((i + j) % 2 != 0)
                result[i][j] *= -1;
        }
    }

    return result;
}

List<List<double>> GetTransposeMatrix(List<List<double>> matrix)
{
    List<List<double>> result = new List<List<double>>(matrix.Count);
    for (int i = 0; i < matrix.Count; i++)
    {
        List<double> row = new List<double>(matrix[i].Count);
        for (int j = 0; j < matrix[i].Count; j++)
        {
            row.Add(0);
        }
        result.Add(row);
    }

    for (int i = 0; i < matrix.Count; i++)
    {
        for (int j = 0; j < matrix[i].Count; j++)
        {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

List<List<double>> GetInverseMatrix(List<List<double>> matrix, double determinate)
{
    List<List<double>> result = [];
    for (int i = 0; i < matrix.Count; i++)
    {
        List<double> row = [];
        for (int j = 0; j < matrix[i].Count; j++)
        {
            row.Add(matrix[i][j] / determinate);
        }
        result.Add(row);
    }
    return result;
}

State MultiplyMatrices(List<List<double>> first, List<double> second)
{
    List<List<double>> result = [];
    for (int i = 0; i < first.Count; i++)
    {
        List<double> row = [];
        double sum = 0;
        for (int j = 0; j < first[i].Count; j++)
        {
            sum += first[i][j] * second[j];
        }
        row.Add(sum);
        result.Add(row);
    }
    return new State(result[0][0], result[1][0]);
}


List<List<Equation>> matrix = [];

matrix.Add(new List<Equation> { new ("x", "x * x"),
                                new ("y", "y * y * y"),
                                new ("x", "-4")});
matrix.Add(new List<Equation> { new ("x", "x / y"),
                                new ("y", "x / y"),
                                new ("x", "-2")});

List<List<SymbolicExpression>> derivativeMatrix = GetDerivativeMatrix(matrix);

Painter.PrintMatrix(matrix);
Painter.PrintMatrix(derivativeMatrix);

State state = new State(2, 1);
State previousState = new State(0, 0);

double epsilon = 0.001;
int i = 1;

var xSubtraction = Math.Abs(Math.Abs(state.X) - Math.Abs(previousState.X));
var ySubtraction = Math.Abs(Math.Abs(state.Y) - Math.Abs(previousState.Y));

var maxValue = Math.Max(xSubtraction, ySubtraction);

Console.Write("Enter the method: ");
string? method = Console.ReadLine();

if (method == null)
    return;

while (maxValue >= epsilon)
{
    Console.WriteLine($"--------------------------------------------------------\nStep {i}\n");
    Console.WriteLine($"X({i - 1}) = [{state.X} {state.Y}]\n");
    List<List<double>> jacobMatrix = GetJacobMatrix(derivativeMatrix, state);
    List<double> result = GetResults(matrix, state);
    Console.WriteLine("Jacob matrix:");
    Painter.PrintMatrix(jacobMatrix, result);
    State? newState;
    if (method.Equals("1"))
    {
        double determinate = GetDeterminate(jacobMatrix, result);
        Console.WriteLine("Determinate: " + determinate + "\n");
        var minor = GetMinor(jacobMatrix);
        Console.WriteLine("Minor:");
        Painter.PrintMatrix(minor);
        var transposeMinor = GetTransposeMatrix(minor);
        Console.WriteLine("Transpose minor:");
        Painter.PrintMatrix(transposeMinor);
        var inverseMatrix = GetInverseMatrix(transposeMinor, determinate);
        Console.WriteLine("Inverse matrix:");
        Painter.PrintMatrix(inverseMatrix);
        newState = MultiplyMatrices(inverseMatrix, result);
    }
    else if (method.Equals("2"))
    {
        newState = Gaus.DirectGauss(jacobMatrix, result);
    }
    else
    {
        return;
    }

    if (newState == null)
        return;

    Console.WriteLine($"Y({i - 1}) = [{newState.X} {newState.Y}]\n");

    previousState = new State(state.X, state.Y);
    state.SubtractState(newState);
    Console.WriteLine($"X({i}) = [{state.X} {state.Y}]\n");

    xSubtraction = Math.Abs(Math.Abs(state.X) - Math.Abs(previousState.X));
    ySubtraction = Math.Abs(Math.Abs(state.Y) - Math.Abs(previousState.Y));

    maxValue = Math.Max(xSubtraction, ySubtraction);

    Console.WriteLine("Delta: " + maxValue);

    i++;
}