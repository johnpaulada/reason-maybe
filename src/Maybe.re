type maybe('a) =
  | Just('a)
  | Nothing
;

type maybe_('a, 'b) = {
  map : ('a => 'b) => maybe_('a, 'b),
  value : 'a => 'a,
  reduce: ('a => 'b) => option('b)
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

let branch = (left : (unit => 'b), right : ('a => 'b), x : maybe('a)) : maybe('b) =>
  switch x {
    | Just(v) => Just(v |> right)
    | Nothing => Just(left())
  }
;

/* Reverse Pipe */
let (<|) = (x, y) => y |> x;

/* Pipe Compose */
let (>>) = (x, y) => z => z |> x |> y;

/* Compose */
let (<<) = (x, y) => z => z |> y |> x;

/* Map */
let (||>) = (x, y) => y |> map <| x

/* Chain */
let (|||>) = (x, y) => y |> chain <| x

/* Value */
let (>|) = (x, y) => y |> value <| x

/* Reduce */
let (>||) = (x, y) => y |> reduce <| x

/* Branch */
let (<->) = (x, y) => z => z |> branch(x, y)

let rec create = (x : option('a)) => {
  map : (fn) => {
    switch x {
      | Some(v) => {
          let mapped = Just(v) ||> fn;

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
      | Some(y) => Just(y) >| v
      | None => Nothing >| v
    }
  },
  reduce : (fn) => {
    switch x {
      | Some(y) => Just(y) >|| fn
      | None => Nothing >|| fn
    }
  }
}