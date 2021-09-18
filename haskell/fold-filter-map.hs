fold :: ([b] -> a -> [b]) -> [b] -> [a] -> [b]
fold f init [] = init
fold f init lst = fold f (f init (head lst)) (tail lst)

filterHelper :: (a -> Bool) -> [a] -> a -> [a]
filterHelper f acc x = if f x then acc ++ [x] else acc

filter :: (a -> Bool) -> [a] -> [a]
filter f = fold (filterHelper f) []

mapHelper :: (a -> b) -> [b] -> a -> [b]
mapHelper f acc x = acc ++ [f x]

map :: (a -> b) -> [a] -> [b]
map f = fold (mapHelper f) []

main :: IO ()
main = do print (Main.map (rem 2) [1, 2, 3])