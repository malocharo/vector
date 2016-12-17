#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
    void **_data;
    int _size;
    int _nb_elem;
    int _iterator;

} vector;

void vector_init(vector *);
void vector_init_size(vector *, int);
int  vector_size(vector *);
int  vector_max_size(vector *);
void vector_del(vector *);
void vector_erase(vector *,int);

void vector_resize(vector *, int);
void vector_shrink(vector *);
void vector_add(vector *, void *);
void vector_insert(vector *,int,void *);
int  Isvector_empty(vector *);
void vector_add_begin(vector *,void *);
void vector_display(vector *);
int  iterator_begin(vector *);
int  iterator_end(vector *);
//<-------------------------NEVER TESTED-------------------------------------------->
void *vector_get(vector *, int);
void vector_swap_elem(vector *,int,int);
void vector_swap_vector(vector *, vector *);
void vector_erase_more(vector *, int, int);

int main()
{

    exit(0);
}
void vector_erase_more(vector *v, int index1, int index2)
{int i;
    if(index1 > v->_nb_elem || index2 > v->_nb_elem) return;
    if(index1 < 0 || index2 < 0) return;
    if(index1 == index2) vector_erase(&v,index1);
    if(index2 < index1)
    {
        int tmp = index1;
        index 1 = index2;
        index2 = tmp;
    }

    for(i = index1;i<index2;i++)
    {
        vector_erase(&v,i);
    }


}
void vector_swap_vector(vector *v, vector *c)
{int i;
    if(!v || !c) return;
    vector a;
    vector_init(&a);
    for(i=0;i < v->_nb_elem;i++)
    {
        vector_add(&a,v->_data[i]);
    }

    for(i = 0;i<c->_nb_elem;i++)
    {
        vector_add(&v,c->_data[i]);
    }
    for(i =0;i<a._nb_elem;i++)
    {
        vector_add(&c,a._data[i]);
    }
    vector_del(&a);//TODO check if it works m8
}
void vector_swap_elem(vector *v, int index1,int index2)
{
    if(index1 > v->_nb_elem || index2 > v->_nb_elem) return;
    if(index1 < 0 || index2 < 0) return;

    vector_add(&v,v->_data[index2]);
    v->_data[index2] = NULL;
    v->_data[index2] = v->_data[index1];
    v->_data[index1] = NULL;
    v->_data[index1] = v->_data[iterator_end(&v)];// TODO test
}
void *vector_get(vector *v, int index)
{
    if(index > v->_nb_elem) return;

    return v->_data[index];
}
void vector_display(vector *v)
{
    int i;
    for(i = 0;i<iterator_end(v);i++)
    {
        printf("%d : %d: %p \n",v->_size,v->_nb_elem,v->_data[i]);
    }
}
void vector_init(vector *v)
{
    v->_size = 10;
    v->_nb_elem = 0;
    v-> _data = malloc(sizeof(void *) *v->_size);
    v->_iterator = 0;
}
void vector_init_size(vector *v, int size)
{
    if(!size) return;

    v->_size = size;
    v->_nb_elem = 0;
    v->_data = malloc(sizeof(void *)*v->_size);
    v->_iterator =0;

}
int vector_size(vector *v)
{
    return v->_nb_elem;
}

void vector_del(vector *v)
{
    free(v->_data);
}
void vector_resize(vector *v, int i)
{
    void **tmp = realloc(v->_data,sizeof(void *) * i);
    if(tmp)
    {
        v->_data = tmp;
        v->_size = i;
    }
}

void vector_add(vector *v, void* data)
{
    if(!data) return;
    if(v->_size == v->_nb_elem)

        vector_resize(v, v->_size*2);

    v->_data[v->_nb_elem] = data;
    v->_nb_elem++;
}

void vector_erase(vector *v, int pos)
{

    if(pos-1 <= 0 || pos >v->_nb_elem) return;
    int a;
    v->_data[pos-1]  = NULL;

    for(a=pos-1;a<v->_nb_elem;a++)
    {
        v->_data[a] = v->_data[a+1];
        v->_data[a+1] = NULL;
    }
    v->_nb_elem--;
}

void vector_insert(vector *v, int pos, void* data)
{
    int i;
    if(!data) return;
    if(pos < 0 || pos >v->_nb_elem) return;
    if(v->_size == v->_nb_elem)
        vector_resize(v, v->_size*2);

    vector_add(v,NULL);

    for(i=v->_nb_elem;i>pos;i--)
    {
        v->_data[i] = v->_data[i-1];
        v->_data[i-1] = NULL;
    }
    v->_data[pos] = data;

}

int vector_max_size(vector *v)
{
    return v->_size;
}

int Isvector_empty(vector *v)
{

    if(v->_nb_elem) return v->_size;

    return 0;
}
void vector_add_begin(vector *v ,void* data)
{
    int i;
    if(!data) return;
    if(v->_size == v->_nb_elem)
        vector_resize(v,v->_size*2);

//vector_add(v,NULL);
    for(i =v->_nb_elem;i>0;i--)
    {
        v->_data[i] = v->_data[i-1];
        v->_data[i-1] = NULL;
    }
    v->_data[0] = data;
    v->_nb_elem++;
}

int iterator_begin(vector *v)
{
    return  v->_iterator = 0;
}

int iterator_end(vector *v)
{
    return v->_iterator = v->_nb_elem;
}

void vector_shrink(vector *v)
{
    if(v->_size == v->_nb_elem) return;
    if(!v->_nb_elem) vector_del(v);
    vector_resize(v,v->_nb_elem);

}
