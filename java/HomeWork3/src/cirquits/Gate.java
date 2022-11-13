package cirquits;

public abstract class Gate {
    protected Gate[] inGates;
    protected int length;
    public Gate(Gate[] inGates) {
        this.inGates = inGates;
        this.length = inGates.length;
    }
    public boolean calc() throws CircuitException{
        return false;
    }
    protected abstract boolean func(boolean[] inValues) throws CircuitException;
    public abstract String getName();
    public abstract Gate simplify();
    public String toString() {
        return null;
    }
}
