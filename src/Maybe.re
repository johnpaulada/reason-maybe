type maybe('a) =
  | Just('a)
  | Nothing
;

let identity = x => x

let from = (x : option('a)) : maybe('a) => 
  switch x {
    | Some(v) => Just(v)
    | None => Nothing
  }
;

let map = (fn : ('a => 'b), x : maybe('a)) : maybe('b) =>
  switch x {
    | Just(v) => Just(fn(v))
    | Nothing => Nothing
  }
;

let reduce = (fn : ('a => 'b), x : maybe('a)) : option('b) =>
  switch x {
    | Just(v) => Some(fn(v))
    | Nothing => None
  }
;

let chain = (fn : ('a => maybe('b)), x : maybe('a)) : maybe('b) =>
  switch x {
    | Just(v) => {
      let value = fn(v) |> reduce(x => x);

      switch value {
        | Some(y) => Just(y)
        | None => Nothing
      }
    };
    | Nothing => Nothing
  }
;

let value = (default : 'a, x : maybe('a)) : option('a) =>
  switch x {
    | Just(v) => Some(v)
    | Nothing => Some(default)
  }
;

let ap = (fn : maybe('a => 'b), x : maybe('a)) : maybe('b) =>
  switch x {
    | Just(v) =>
      switch fn {
        | Just(y) => Just(v |> y)
        | Nothing => Nothing
      }
    | Nothing => Nothing
  }
;

let branch = (left : ('a => 'b), right : ('a => 'b), x : maybe('a)) : maybe('b) =>
  switch x {
    | Just(v) => Just(v |> right)
    | Nothing => Just(left())
  }
;