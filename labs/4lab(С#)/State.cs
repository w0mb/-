namespace _4lab
{
    public class State
    {
        public State(double x, double y)
        {
            X = x;
            Y = y;
        }

        public void SubtractState(State newState)
        {
            X -= newState.X;
            Y -= newState.Y;
        }

        public double X { get; set; }
        public double Y { get; set; }
    }
}