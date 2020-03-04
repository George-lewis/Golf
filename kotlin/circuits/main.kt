fun main(args: Array<String>) {

    c1(true, false, true)

    println("----------")

    c1(false, true, false)

    println("----------")

    c1(true, true, true)

    println("----------")

    for (i in 0..8) {

        val s = Integer.toBinaryString(i).padStart(3, '0').toCharArray()

        val z = s.map { c -> Integer.parseInt(Character.toString(c).padStart(3, '0')) }.map { i -> i == 1 }.toList()

        println(z)

        c2(z.get(0), z.get(1), z.get(2))

        println("----")

    }

}

fun c1(a: Boolean, b: Boolean, c: Boolean) {

    val inp = gengate(3)

    val pri = printgate()

    val and = andgate()
    val not = notgate()
    val xor = xorgate()
    val or = orgate()
    val junct = junction(2)

    inp.connect(and, 0)
    inp.connect(not, 1)
    not.connect(junct)
    junct.connect(and)
    junct.connect(xor, 1)
    inp.connect(xor, 2)

    xor.connect(or)

    and.connect(or)

    or.connect(pri)

    inp.output(0).state = a

    inp.output(1).state = b

    inp.output(2).state = c



}

fun c2(a: Boolean, b: Boolean, c: Boolean) {

    val inp = gengate(3)
    val out = printgate()

    val not1 = notgate()
    val not2 = notgate()
    val not3 = notgate()
    val and1 = andgate()
    val and2 = andgate()
    val nand = nandgate()
    val or = orgate()
    val xor = xorgate()
    val jun1 = junction(2)
    val jun2 = junction(2)
    val jun3 = junction(2)

    inp.connect(not1)
    inp.connect(jun1)
    inp.connect(nand)

    not1.connect(and1)

    jun1.connect(and2)

    nand.connect(jun2)

    jun1.connect(nand, 1)

    jun2.connect(and2)
    jun2.connect(not3, 1)

    and2.connect(jun3)

    jun3.connect(and1)
    jun3.connect(xor, 1)

    not3.connect(xor)

    xor.connect(or)

    and1.connect(not2)

    not2.connect(or)

    or.connect(out)

    inp.output(0).state = a
    inp.output(1).state = b
    inp.output(2).state = c

}