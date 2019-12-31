//
// The goal is to reimplement Observer and Observable myself
// Then demonstrate its functionality
//
// The classes Observer and Observable have been implemented by me
// Switch implements Observable and Light implements Observer
// Ergo lights observe switches
//
// When a switch is flipped on it will notify all of its connected
// Lights and so they will light up as well
//
// In theory you could have one light connected to multiple switches
// For a more complicated system
//

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
