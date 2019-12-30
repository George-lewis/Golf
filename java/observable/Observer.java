import java.util.ArrayList;
import java.util.List;

public abstract class Observer<T> {
 
    private List<Observable<T>> observables = new ArrayList<>();

    public abstract void update(Observable<T> o, T val);

    public void observes(Observable<T> o) {
        observables.add(o);
    }

    public List<Observable<T>> observables() {
        return observables;
    }

}