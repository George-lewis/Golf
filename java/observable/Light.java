public class Light extends Observer<Boolean> {

    boolean on = false;

    @Override
    public void update(Observable<Boolean> o, Boolean val) {
        
        if (this.observables().stream().map(obs -> obs.get()).allMatch(b -> !b))
            this.on = false;
        else
            this.on = true;

    }

    public boolean isOn() { return on; }

}