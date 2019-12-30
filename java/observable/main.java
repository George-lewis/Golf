public class main {

    public static void main(String[] args) {

        Switch s1 = new Switch();

        Switch s2 = new Switch();

        Light l = new Light();

        s1.addObserver(l);

        s2.addObserver(l);

        System.out.println(l.isOn());

        s1.flip();

        System.out.println(l.isOn());
        
        s1.flip();

        System.out.println(l.isOn());

        s2.flip();

        System.out.println(l.isOn());

        s2.flip();

        System.out.println(l.isOn());

    }

}