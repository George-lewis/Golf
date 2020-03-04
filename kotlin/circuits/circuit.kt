data class connection(val input: gate, var output: gate? = null, private val _state: Boolean = false) {

    var state: Boolean = _state
    set(value) {
        field = value
        this.notify()
    }

    public fun notify() = output?.update()

    override fun toString(): String = "Connection: ${state}"

}

abstract class gate {

    val inputs: MutableList<connection> = mutableListOf()

    val outputs: MutableList<connection> = mutableListOf()

    fun input(n: Int): connection = inputs.get(n)

    open fun output(n: Int): connection = outputs.get(n)

    constructor(no: Int) {

        for (i in 0..no) {
            outputs.add(connection(input = this))
        }

    }

    abstract fun update()

    fun connect(g: gate, out: Int = 0, _in: Int? = null) {

        output(out).output = g

        if (_in == null) {
            g.inputs.add(output(out))
        } else {
            g.inputs.add(_in, output(out))
        }

    }

}

class junction(n: Int) : gate(n) {

    override fun update() {

        for (c in outputs) {
            c.state = input(0).state
        }

    }

}

class orgate : gate(1) {

    override fun update() {

        for (iconn in inputs) {

            if (iconn.state) {

                output(0).state = true

                return

            }
        }

        output(0).state = false

    }

}

class notgate: gate(1) {

    override fun update() {

        output(0).state = !input(0).state

    }

}

class andgate: gate(1) {

    override fun update() {

        if (inputs.all { c -> c.state }) {
            output(0).state = true
        } else {
            output(0).state = false
        }

    }

}

class xorgate: gate(1) {

    override fun update() {

        if ( (input(0).state && !input(1).state) || (!(input(0).state && input(1).state)) ) {
            output(0).state = true
        } else {
            output(0).state = false
        }

    }

}

class nandgate: gate(1) {

    override fun update() {

        output(0).state = !(input(0).state && input(1).state)

    }

}

class gengate(no: Int): gate(no) {

    override fun update() {}

}

class printgate: gate(0) {

    override fun update() {

        for (c in inputs) {
            println(c)
        }

    }

}

class outgate(val outstr: (b: Boolean) -> String): gate(0) {

	override fun update() {

			for (c in inputs) {
				println(outstr(c.state))
			}

	}

}
