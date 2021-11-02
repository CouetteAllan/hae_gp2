#pragma once


template<typename Value>
class Tree {
public:
	Value   v = {};
	Tree*   l = nullptr;
	Tree*   r = nullptr;

	Tree(Value _v) {
		this->v = _v;
	}

	Tree(Value _v, Tree* _l, Tree* _r) {
		v = _v;
		l = _l;
		r = _r;
	}

	Tree* insert(Value v) {

		if (this->v > v) {
			if (r)
				r->insert(v);
			else
				r = new Tree(v);
		}
		else {
			if (l)
				l->insert(v);
			else
				l = new Tree(v);
		}
		return this;
	}

	Tree* merge(Tree* other) {
		Value vo = other->v;

		insert(vo);

		if (other->l)
			merge(other->l);
		if (other->r)
			merge(other->r);

		delete other;

		return this;

	}

	Tree* remove(Value vr) {
		if (vr == v) {
			auto _l = l;
			auto _r = r;
			if (!l) {
				delete this;
				return _r;
			}
			else if (!r) {
				delete this;
				return _l;
			}
			else {
				l->merge(r);
				delete this;
				return _l;
			}
		}
		else {
			if (vr < v) {
				if (l)
					l = l->remove(vr);
			}
			else
				if (r)
					r = r->remove(vr);
		}

		return this;
	}

	Tree* search(Value vs) {
		if (vs == v)
			return this;
		else {
			if (vs > v) {
				if (r)
					r->search(vs);
				else
					return nullptr;
			}
			else {
				if (l)
					l->search(vs);
				else
					return nullptr;
			}
		}

	}



};