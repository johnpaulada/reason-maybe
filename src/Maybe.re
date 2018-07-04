type maybe('a) =
  | Just('a)
  | Nothing
;

type maybe_('a, 'b) = {
  map : ('a => 'b) => maybe_('a, 'b),
  value : 'a => 'a
}

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
      let value = fn(v) |> reduce(identity);

      switch value {
        | Some(y) => Just(y)
        | None => Nothing
      }
    };
    | Nothing => Nothing
  }
;

let value = (default : 'a, x : maybe('a)) : 'a =>
  switch x {
    | Just(v) => v
    | Nothing => default
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

let rec create = (x : option('a)) => {
  map : (fn) => {
    switch x {
      | Some(v) => {
          let mapped = map(fn, Just(v));

          switch mapped {
            | Just(v) => create(Some(v))
            | Nothing => create(None)
          }
        }
      | None => create(None)
    }
  },
  value : (v) => {
    switch x {
      | Some(y) => value(v, Just(y))
      | None => value(v, Nothing)
    }
  }
}

/* Pipe */
let (>>) = (x, y) => z => z |> x |> y;

/* Compose */
let (<<) = (x, y) => z => z |> y |> x;

/* Map */
let (||>) = (x, y) => x |> (y |> map)

/* Chain */
let (|||>) = (x, y) => x |> (y |> chain)

/* Value */
let (>|) = (x, y) => x |> (y |> value)

/* Reduce */
let (>||) = (x, y) => x |> (y |> reduce)

/* Branch */
let (<->) = (x, y) => z => branch(x, y, z)