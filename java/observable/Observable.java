import java.util.ArrayList;
import java.util.List;

public class Observable<T> {

    private List<Observer<T>> observers = new ArrayList<Observer<T>>();

    private T val;

    public Observable(T val) {
        this.val = val;
    }

    public void notifyObservers() {

        for (Observer<T> o : observers) {

            o.update(this, val);            

        }

    }

    public void set(T val) {
        this.val = val;
        this.notifyObservers();
    }

    public T get() {
        return this.val;
    }

    public void addObserver(Observer<T> o) {
    
        o.observes(this);

        this.observers.add(o);
        
    }

    public boolean removeObserver(Observer<T> o) {

        return observers.remove(o);

    }

}