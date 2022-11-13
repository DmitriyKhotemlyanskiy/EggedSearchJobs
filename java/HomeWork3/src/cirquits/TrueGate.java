package cirquits;

public class TrueGate extends Gate{
    private static Gate instance = null;


    public static Gate instance() {
        if(instance == null)
            instance = new TrueGate();
        return instance;
    }
    @Override
    protected boolean func(boolean[] inValues) throws CircuitException {
        // TODO Auto-generated method stub
        return false;
    }
    @Override
    public String getName() {
        // TODO Auto-generated method stub
        return "T";
    }
    @Override
    public Gate simplify() {
        // TODO Auto-generated method stub
        return null;
    }
}
