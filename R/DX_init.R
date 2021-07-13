dx_init <- function(seed=12345, K_X1=47, B_X1=536869888) {
  set.seed(seed)
  .Random.seed[3] <<- K_X1
  .Random.seed[4] <<- B_X1
  .Random.seed <<- as.integer(.Random.seed)
}