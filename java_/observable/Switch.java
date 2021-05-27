public class Switch extends Observable<Boolean> {

    public Switch() {
        super(false);
    }

    public void flip() {
        this.set(!this.get());
    }

}