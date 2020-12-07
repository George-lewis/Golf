const SCANNER = Java.type('java.util.Scanner')
const SYSTEM = Java.type('java.lang.System')

const sc = new SCANNER(SYSTEM.in);

const ALPHABET = [...'ABCDEFGHIJKLMNOPQRSTUVWXYZ']

const ceasar = (str) => [...(str.toUpperCase())].map(c => alphabet[(alphabet.indexOf(c) + 1) % alphabet.length]).join('');

while (true) {
	var line = sc.nextLine();
	if (!line) continue;
	console.log(`${line} => ${ceasar(line)}`);
}
