# reason-maybe
A simple Maybe library in Reason.

[![forthebadge](https://forthebadge.com/images/badges/gluten-free.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

[![Made with Reason](https://img.shields.io/badge/Made%20with-Reason-red.svg?longCache=true&style=for-the-badge)](https://reasonml.github.io/)

## Installation
- Install [Yarn](https://yarnpkg.com).
- Run `yarn add reason-maybe`.
- Add `reason-maybe` to your `bs-dependencies` in `bsconfig.json`

**`bsconfig.json`**
```json
"bs-dependencies": [
  "reason-maybe"
]
```

## Usage

### `from`
To create a Maybe use `Maybe.from`:
```reason
let one = Maybe.from(Some(1)); /* Just(1) */
```

### `map`
To map a function on the Maybe, use `Maybe.map`:
```reason
let plusOne = x => x + 1;
let onePlusOne = one |> Maybe.map(plusOne); /* Just(2) */
```

Alternatively, you can import the equivalent infix operator `||>`:
```reason
let (||>) = Maybe.(||>);

let onePlusOne = one ||> plusOne; /* Just(2) */
```

If the map operation provides a value, it will return `Just(value)`. Else, it will return a `Nothing`.

### `value`
To extract the value of the Maybe, we need to use `Maybe.value`:
```reason
let value = onePlusOne |> Maybe.value(0); /* 2 */
```

Alternatively, you can import the equivalent infix operator `>|`:
```reason
let (>|) = Maybe.(>|);

let value = onePlusOne >| 0; /* 2 */
```

If the Maybe was actually a `Nothing`, the value given to the `Maybe.value` function will be the resulting value.
In this case if `onePlusOne` was `Nothing`, the value of `value` would be `0`.

### `chain`
To run a function that returns a Maybe on a Maybe, we use `Maybe.chain`:
```reason
let two = Maybe.from(Some(2));
let plusOneMaybe = x => one |> Maybe.map(y => x + y);
let twoPlusOneMaybe = two |> Maybe.chain(plusOneMaybe); /* Just(3) */
```

Alternatively, you can import the equivalent infix operator `|||>`:
```reason
let (|||>) = Maybe.(|||>);

let twoPlusOneMaybe = two |||> plusOneMaybe; /* Just(3) */
```

We use the `plusOneMaybe` function which returns a Maybe on the `two` Maybe.
Instead of `Maybe.map`, we use `Maybe.chain` to lift it from the returned Maybe unto the current Maybe.

### `branch`
If the Maybe has turned into a Nothing and you want to handle that, you can use `Maybe.branch`:
```reason
let addToRoute = s => x =>
  switch s {
    | "" => Maybe.Nothing
    | v => Maybe.Just(x ++ v)
  }
;
let noslug = () => "/not_found";
let hasslug = v => v
let getArticleRoute = slug => Maybe.from(Some("/articles/"))
  |> Maybe.chain(addToRoute(slug))
  |> Maybe.branch(noslug, hasslug)
  |> Maybe.value("/articles");

let validArticleRoute = getArticleRoute("awesome");
Js.log(validArticleRoute); /* /articles/awesome */

let invalidArticleRoute = getArticleRoute("");
Js.log(invalidArticleRoute); /* /not_found */
```

If the Maybe is a `Just`, the `hasslug` method will be called. If the Maybe is a `Nothing`, the `noslug` will be called.

If want it to be less verbose, you can import and use the equivalent infix operator `<->`:
```reason
let (<->) = Maybe.(<->);
let (|||>) = Maybe.(|||>);
let (>|) = Maybe.(>|);

/* Previously defined functions here */

let getArticleRoute = slug =>
    Maybe.from(Some("/articles/"))
        |||> addToRoute(slug)
        |> (noslug <-> hasslug)
        >| "/articles"
;

let validArticleRoute = getArticleRoute("awesome");
Js.log(validArticleRoute); /* /articles/awesome */

let invalidArticleRoute = getArticleRoute("");
Js.log(invalidArticleRoute); /* /not_found */
```

This form is less readable but more terse yields the same result.

## Development

1. Clone this repo.
2. Move to this directory with `cd reason-maybe`.
3. Install [Yarn](https://yarnpkg.com).
4. Run `yarn`.

### Build
```
npm run build
```

### Build + Watch

```
npm run start
```

## License
MIT